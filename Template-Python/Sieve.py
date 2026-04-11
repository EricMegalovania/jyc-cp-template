from array import array


pri = []
notp = array('b', [0] * N)
notp[1] = 1
for i in range(2, N):
    if not notp[i]:
        pri.append(i)
    for p in pri:
        x = i * p
        if x >= N:
            break
        notp[x] = 1
        if i % p == 0:
            break