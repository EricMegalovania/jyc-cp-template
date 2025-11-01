#! /bin/bash
g++ "$1.cpp" -pedantic -O2 -std=c++20 -pipe \
	-Wall -Wextra -Wshadow -Wconversion \
	-fstack-protector-strong -g \
	-o "$1" -lm
