#! /bin/bash
g++ "$1.cpp" -pedantic -O2 -std=c++2a -pipe -Wall -Wextra -Wshadow -Wconversion -g -lm -W -fstack-protector-strong -s -o "$1.exe"
