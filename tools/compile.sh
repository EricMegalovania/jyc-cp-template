#!/bin/bash
g++ "$1.cpp" -pedantic -std=c++20 -O1 -pipe \
    -fsanitize=address,undefined \
    -fno-omit-frame-pointer \
    -fsanitize-address-use-after-scope \
    -Wall -Wextra -Wshadow -Wconversion \
    -fstack-protector-strong -g -lm -no-pie \
    -o "$1"
