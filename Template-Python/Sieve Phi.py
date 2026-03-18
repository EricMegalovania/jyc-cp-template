pri = []
not_prime = [False] * N
not_prime[1] = True
phi = [1] * N
for i in range(2, N):
    if not not_prime[i]:
        pri.append(i)
        phi[i] = i - 1
    for pri_j in pri:
        x = i * pri_j
        if x >= N:
            break
        not_prime[x] = True
        if i % pri_j == 0:
            phi[x] = phi[i] * pri_j
            break
        phi[x] = phi[i] * phi[pri_j]