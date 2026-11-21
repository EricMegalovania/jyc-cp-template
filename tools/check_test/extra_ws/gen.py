import os

i = 0
if os.path.exists("gen_count.txt"):
    with open("gen_count.txt") as f:
        s = f.read().strip()
        if s:
            i = int(s)
i += 1
with open("gen_count.txt", "w") as f:
    f.write(str(i))
print(i)
