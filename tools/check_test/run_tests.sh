#!/bin/bash
set -u

cd "$(dirname "$0")" || exit 1

TIME_LIMIT=${TIME_LIMIT:-600}

preflight() {
    local miss=0 x
    for x in bash timeout grep clang++ pypy mktemp; do
        if ! command -v "$x" > /dev/null 2>&1; then
            echo "missing required command: $x" >&2
            miss=1
        fi
    done
    return "$miss"
}
preflight || exit 1

tmp=$(mktemp -d) || exit 1
trap 'rm -rf "$tmp"' EXIT

failures=$tmp/failures
: > "$failures"

total=0
passed=0

pick() {
    if [[ -f "$1/$2.cpp" ]]; then
        printf '%s\n' "$1/$2.cpp"
    elif [[ -f "$1/$2.py" ]]; then
        printf '%s\n' "$1/$2.py"
    fi
}

clean_artifacts() {
    local d=$1
    rm -f wa_in.txt wa_out.txt wa_ans.txt gen_count.txt
    rm -f "$d/wa.exe" "$d/ac.exe" "$d/gen.exe" \
          "$d/wa" "$d/ac" "$d/gen"
    rm -f "$d/wa_in.txt" "$d/wa_out.txt" "$d/wa_ans.txt" \
          "$d/gen_count.txt"
}

rc_matches() {
    local exp=$1 act=$2
    if [[ $exp == nonzero ]]; then
        (( act != 0 && act != 124 ))
    else
        (( act == exp ))
    fi
}

check_kind() {
    local kind=$1 log=$2
    case $kind in
        ok) ! grep -qE 'AddressSanitizer|runtime error|Traceback' "$log" ;;
        diff) grep -q 'wa_out.txt' "$log" && grep -q 'wa_ans.txt' "$log" ;;
        asan) grep -q 'AddressSanitizer' "$log" ;;
        traceback) grep -q 'Traceback' "$log" ;;
        usage) grep -q 'check wa ac gen' "$log" ;;
        *) return 1 ;;
    esac
}

run_case() {
    local name=$1 exp_rc=$2 exp_tests=$3 kind=$4
    local log=$name/run.log
    local rc=0 tests=0
    local -a problems=()

    total=$((total + 1))
    clean_artifacts "$name"

    if [[ ! -d $name ]]; then
        problems+=("missing case directory")
    elif [[ $name == guard ]]; then
        timeout "$TIME_LIMIT" bash ./check.sh > "$log" 2>&1 || rc=$?
    else
        local w a g
        w=$(pick "$name" wa)
        a=$(pick "$name" ac)
        g=$(pick "$name" gen)
        if [[ -z $w || -z $a || -z $g ]]; then
            problems+=("missing wa/ac/gen source")
        else
            timeout "$TIME_LIMIT" bash ./check.sh "$w" "$a" "$g" > "$log" 2>&1 || rc=$?
        fi
    fi

    if [[ -f $log ]]; then
        tests=$(grep -cE '^Test [0-9]+$' "$log" 2> /dev/null || true)
    fi

    if ((${#problems[@]} == 0)); then
        rc_matches "$exp_rc" "$rc" ||
            problems+=("exit code: expected $exp_rc, got $rc")
        ((tests == exp_tests)) ||
            problems+=("test count: expected $exp_tests, got $tests")
        check_kind "$kind" "$log" ||
            problems+=("failure kind: expected '$kind'")
    fi

    if ((${#problems[@]} == 0)); then
        passed=$((passed + 1))
        printf 'PASS  %-12s rc=%s tests=%s\n' "$name" "$rc" "$tests"
    else
        printf 'FAIL  %-12s rc=%s tests=%s log=%s\n' "$name" "$rc" "$tests" "$log"
        local p
        for p in "${problems[@]}"; do
            printf '      %s\n' "$p"
        done
        printf '%s\n' "$name" >> "$failures"
    fi

    clean_artifacts "$name"
}

while read -r name exp_rc exp_tests kind; do
    [[ -z $name || $name == \#* ]] && continue
    run_case "$name" "$exp_rc" "$exp_tests" "$kind"
done << 'EOF'
cpp_ok        0       100 ok
cpp_bad       nonzero 2   diff
cpp_re_ac     nonzero 4   asan
cpp_re_gen    nonzero 5   asan
cpp_re_wa     nonzero 3   asan
py_ok         0       100 ok
py_bad        nonzero 2   diff
py_re_ac      nonzero 4   traceback
py_re_gen     nonzero 5   traceback
py_re_wa      nonzero 3   traceback
mixed_ok      0       100 ok
extra_ws      0       100 ok
guard         1       0   usage
EOF

printf '\n%d/%d cases passed\n' "$passed" "$total"
if ((passed != total)); then
    echo 'failed cases:'
    sed 's/^/  - /' "$failures"
    exit 1
fi
