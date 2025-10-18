# -*- coding: UTF-8 -*-
file_read, file_write = "", ""
fast_input, fast_output = 0, 1
dfs, hashing = 1, 0
de = 1  # 调试输出开关

import io, os, sys
from io import BytesIO, IOBase
import random
import bisect  # 二分查找
from collections import Counter, defaultdict, deque  # 常用集合类
from copy import deepcopy  # 深拷贝
from functools import cmp_to_key, lru_cache, reduce  # 函数工具

# 堆操作
from heapq import merge, heapify, heappop, heappush, heappushpop, nlargest, nsmallest, heapreplace

# 迭代工具
from itertools import accumulate, combinations, permutations, count, product

# 运算符
from operator import add, iand, ior, itemgetter, mul, xor

# 字符串常量
from string import ascii_lowercase, ascii_uppercase, ascii_letters

# 类型提示
import typing
from typing import *

import math
inf = math.inf  # 无穷大常量

# 以下处理输入
if file_read:
    sys.stdin = open(file_read, "r")

if fast_input:
    # 一次性读取所有输入到缓冲区
    input_lines = sys.stdin.read().splitlines()
    input_index = 0
    
    # 创建输入函数
    def input():
        global input_index
        if input_index < len(input_lines):
            line = input_lines[input_index]
            input_index += 1
            return line
        return ""
else:
    input = lambda: sys.stdin.readline().strip()  # 快速输入函数

# 输入函数集合
def I():  # 读取一行字符串
    return input()

def II():  # 读取一个整数
    return int(input())

def MII():  # 读取多个整数(map对象)
    return map(int, input().split())

def LI():  # 读取一行字符串列表
    return input().split()

def LII():  # 读取一行整数列表
    return list(map(int, input().split()))

def LFI():  # 读取一行浮点数列表
    return list(map(float, input().split()))

def GMI():  # 读取并转换为0-indexed索引(map)
    return map(lambda x: int(x) - 1, input().split())

def LGMI():  # 读取并转换为0-indexed索引(list)
    return list(map(lambda x: int(x) - 1, input().split()))

# 以下处理输出
if fast_output:
    BUFSIZE = 4096  # 缓冲区大小
    class FastIO(IOBase):
        # 快速IO实现
        newlines = 0
        
        def __init__(self, file):
            self._fd = file.fileno()
            self.buffer = BytesIO()
            self.writable = "x" in file.mode or "r" not in file.mode
            self.write = self.buffer.write if self.writable else None
            
        def read(self):
            # 读取实现
            while True:
                b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                if not b:
                    break
                ptr = self.buffer.tell()
                self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
            self.newlines = 0
            return self.buffer.read()
        
        def readline(self):
            # 读取一行
            while self.newlines == 0:
                b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                self.newlines = b.count(b"\n") + (not b)
                ptr = self.buffer.tell()
                self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
            self.newlines -= 1
            return self.buffer.readline()
        
        def flush(self):
            # 刷新缓冲区
            if self.writable:
                os.write(self._fd, self.buffer.getvalue())
                self.buffer.truncate(0), self.buffer.seek(0)
                
    class IOWrapper(IOBase):
        # IO包装器
        def __init__(self, file):
            self.buffer = FastIO(file)
            self.flush = self.buffer.flush
            self.writable = self.buffer.writable
            self.write = lambda s: self.buffer.write(s.encode("utf-8"))
            self.read = lambda: self.buffer.read().decode("utf-8")
            self.readline = lambda: self.buffer.readline().decode("utf-8")

# 统一处理输出重定向
if file_write:
    if fast_output:
        # 二进制模式打开文件 + IOWrapper 包装
        binary_file = open(file_write, "wb")
        sys.stdout = IOWrapper(binary_file)
    else:
        # 直接文本模式重定向
        sys.stdout = open(file_write, "w")
else:
    if fast_output:
        # 包装标准输出的二进制缓冲区
        sys.stdout = IOWrapper(sys.stdout.buffer)

# DFS递归优化（避免递归深度限制）
if dfs:
    from types import GeneratorType
    
    def bootstrap(f, stk=[]):
        # 递归优化装饰器
        def wrappedfunc(*args, **kwargs):
            if stk:
                return f(*args, **kwargs)
            else:
                to = f(*args, **kwargs)
                while True:
                    if type(to) is GeneratorType:
                        stk.append(to)
                        to = next(to)
                    else:
                        stk.pop()
                        if not stk:
                            break
                        to = stk[-1].send(to)
                return to
        return wrappedfunc

# 高效邻接表实现（链式前向星）
class lst_lst:
    def __init__(self, n) -> None:
        self.n = n
        self.pre = []   # 前向指针列表
        self.cur = []   # 值列表
        self.notest = [-1] * (n + 1)  # 头指针数组
    
    # 添加元素
    def append(self, i, j):
        self.pre.append(self.notest[i])
        self.notest[i] = len(self.cur)
        self.cur.append(j)
    
    # 迭代访问
    def iterate(self, i):
        tmp = self.notest[i]
        while tmp != -1:
            yield self.cur[tmp]
            tmp = self.pre[tmp]

# 哈希优化（防止哈希碰撞攻击）
if hashing:
    RANDOM = random.getrandbits(20)  # 随机种子
    class Wrapper(int):
        # 哈希包装器
        def __init__(self, x):
            int.__init__(x)
            
        def __hash__(self):
            return super(Wrapper, self).__hash__() ^ RANDOM

if de:  # 绿色调试输出
    def dbg(*args, **kwargs):
        print('\033[92m', end='', file=sys.stderr)
        print(*args, **kwargs, file=sys.stderr)
        print('\033[0m', end='', file=sys.stderr)
else:
    def dbg(*args, **kwargs):
        return

def main():
    print("Hello World")
    return

multi_test = 1
if __name__ == "__main__":
    T = II() if multi_test else 1
    for _ in range(T):
        main()