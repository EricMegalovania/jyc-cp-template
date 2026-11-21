#!/bin/bash
set -e
[ $# -ge 3 ] || { echo 'check wa ac gen'; exit 1; }

c=${1##*/}
c=${c%.*}

in=${c}_in.txt
out=${c}_out.txt
ans=${c}_ans.txt

PY=pypy  # 根据赛场实际情况变更
cmd() {
    if [[ $1 == *.py ]]; then
        C="$PY $1"
    else
        bash "$HOME/compile.sh" "${1%.cpp}"
        C="./${1%.cpp}"
    fi
}

cmd "$1"; W=$C
cmd "$2"; A=$C
cmd "$3"; G=$C

for ((i=1;i<=100;i++)); do
    echo "Test $i"
    $G > "$in"
    $W < "$in" > "$out"
    $A < "$in" > "$ans"
    diff -ubBZ --color=auto "$out" "$ans" || break
done
