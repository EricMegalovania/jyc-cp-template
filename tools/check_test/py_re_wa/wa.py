n = int(input())
if n >= 3:
    raise RuntimeError("wa RE")
print(n * (n + 1) // 2)
