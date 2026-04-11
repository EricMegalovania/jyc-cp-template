from array import array


pri = []
notp = array('b', [0] * N)
notp[1] = 1
phi = array('i', [1] * N)
for i in range(2, N):
    if not notp[i]:
        pri.append(i)
        phi[i] = i - 1
    for p in pri:
        x = i * p
        if x >= N:
            break
        notp[x] = 1
        if i % p == 0:
            phi[x] = phi[i] * p
            break
        phi[x] = phi[i] * (p - 1)