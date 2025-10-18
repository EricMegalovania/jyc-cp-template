# sieve primes in [2,N-1]
pri = []
not_prime = [False] * N
def sieve():
    for i in range(2, N):
        if not not_prime[i]:
            pri.append(i)
        for pri_j in pri:
            if i * pri_j >= N:
                break
            not_prime[i * pri_j] = True
            if i % pri_j == 0:
                break