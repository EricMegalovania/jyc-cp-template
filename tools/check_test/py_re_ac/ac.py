n = int(input())
if n >= 4:
    raise RuntimeError("ac RE")
print(n * (n + 1) // 2)
