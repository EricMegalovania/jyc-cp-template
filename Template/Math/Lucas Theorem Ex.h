struct EXLB { // Extended Lucas Base
    static void exgcd(int a, int b, int &x, int &y) {
        if (!b)
            x = 1, y = 0;
        else {
            exgcd(b, a % b, y, x);
            y -= a / b * x;
        }
    }
    static int inv(int a, int m) { // a^{-1} % m, requires gcd(a, m) == 1
        int x, y;
        exgcd(a, m, x, y);
        x %= m;
        if (x < 0) x += m;
        return x;
    }
    static int crtc(int m_i, int m) { // CRT 系数: m/m_i * (m/m_i)^(-1) mod m_i
        LL mm = m / m_i;
        mm *= inv(int(mm), m_i);
        return int(mm % m);
    }
};
// C(n, k) mod p^a —— 要求 p 是质数，pa == p^a
struct BMPP : EXLB { // BinomModPrimePower
    int p, a, pa;
    vector<int> f; // f[i] = (1..i 中所有不被 p 整除的数的乘积) mod pa
    BMPP(int p, int a, int pa) : p(p), a(a), pa(pa), f(pa) {
        f[0] = 1;
        for (int i = 1; i < pa; ++i)
            if (i % p == 0)
                f[i] = f[i - 1];
            else
                f[i] = LL(f[i - 1]) * i % pa;
    }
    LL nu(LL n) const { // n! 中 p 的幂次
        LL c = 0;
        do {
            n /= p;
            c += n;
        } while (n);
        return c;
    }
    LL fmod(LL n) const { // (n!)_p mod pa：n! 去掉所有因子 p 之后的值
        bool neg = (p != 2 || pa <= 4); // 单位群全体乘积是否为 -1
        LL res = 1;
        while (n > 1) {
            if (neg && ((n / pa) & 1)) res = pa - res; // 完整块贡献 -1
            res = res * f[n % pa] % pa;
            n /= p;
        }
        return res;
    }
    int C(LL n, LL k) const { // 主接口：C(n, k) mod pa, 要求 0 <= k <= n
        LL v = nu(n) - nu(n - k) - nu(k);
        if (v >= a) return 0; // p^a | C(n, k)
        LL res = fmod(n - k) * fmod(k) % pa;
        res = fmod(n) * inv(int(res), pa) % pa;
        for (; v; --v) res = res * p % pa; // 补回 p 的幂
        return int(res);
    }
};
// C(n, k) mod m —— m 任意正整数, 内部分解素因子后 CRT 合并
struct BM : EXLB { // BinomMod
    int m;
    vector<BMPP> bp;
    vector<LL> crt_m;
    BM(int n) : m(n) {
        for (int p = 2; LL(p) * p <= n; ++p) {
            if (n % p == 0) {
                int a = 0, pa = 1;
                for (; n % p == 0; n /= p, ++a, pa *= p);
                bp.emplace_back(p, a, pa);
                crt_m.push_back(crtc(pa, m));
            }
        }
        if (n > 1) { // 剩下一个大质数
            bp.emplace_back(n, 1, n);
            crt_m.push_back(crtc(n, m));
        }
    }
    int C(LL n, LL k) const { // 主接口: C(n, k) mod m, 要求 0 <= k <= n
        LL res = 0;
        for (int i = 0; i < int(bp.size()); ++i)
            res = (bp[i].C(n, k) * crt_m[i] + res) % m;
        return int(res);
    }
};