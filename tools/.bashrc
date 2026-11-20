alias ZZ="$HOME/compile.sh"
ZA() { ZZ "$1" && "./$1"; }
alias check="$HOME/check.sh"
ulimit -s 1048576  # 千万不能 unlimited, 如果报错就改成 262144 / 524288
