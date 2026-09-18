// C(n, k) mod p —— 要求 p 是质数, 且 p 不大 (要开两个长度 p 的数组)
struct BMP { // BinomModPrime
    int p;
    vector<int> fc, fc_inv;
    BMP(int p) : p(p), fc(p), fc_inv(p) {
        fc[0] = 1;
        for (int i = 1; i < p; ++i)
            fc[i] = LL(fc[i - 1]) * i % p;
        fc_inv[p - 1] = p - 1; // 用 Wilson 定理 (p-1)! = -1 (mod p) 倒推
        for (int i = p - 2; i >= 0; --i)
            fc_inv[i] = LL(fc_inv[i + 1]) * (i + 1) % p;
    }
    int calc(int n, int k) const { // C(n, k) mod p, 要求 0 <= n, k < p
        if (n < k) return 0;
        return LL(fc[n]) * fc_inv[k] % p * fc_inv[n - k] % p;
    }
    int C(LL n, LL k) const { // 主接口: C(n, k) mod p, n, k 可到 1e18
        LL res = 1;
        while (n || k) {
            res = res * calc(n % p, k % p) % p;
            n /= p, k /= p;
        }
        return (int)res;
    }
};