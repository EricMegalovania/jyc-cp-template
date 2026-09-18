// ============== 鲸鱼少女 CRT 通用模板（模数两两互质） ==============
namespace CRT {
    using i128 = __int128_t;
    inline constexpr LL mul(const LL x, const LL y, const LL M) {
        return LL(i128(x) * y % M);
    }
    inline constexpr LL red(LL a, const LL m) {
        a %= m;
        if (a < 0) a += m;
        return a;
    }
    constexpr LL exgcd(LL a, LL b, LL &x, LL &y) { // 扩欧：a*x + b*y = gcd(a, b)
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        LL x1, y1;
        LL g = exgcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - (a / b) * y1;
        return g;
    }
    constexpr LL inv(LL a, LL m) { // 逆元：要求 gcd(a, m) = 1 (m >= 1)
        LL x, y;
        a = red(a, m);
        exgcd(a, m, x, y);
        return red(x, m);
    }
    // ---------- 方案 A：标准 CRT ----------
    // x = a[i] (mod m[i]), m[i] 两两互质
    // 返回最小非负解; M = m[0] * m[1] * ..., 要求 M 不爆 long long
    LL crt(const vector<LL> &a, const vector<LL> &m) {
        const int n = (int)a.size();
        LL M = 1;
        for (LL mi : m) M *= mi; // 会爆就改用 garner
        LL ans = 0;
        for (int i = 0; i < n; i++) {
            LL Mi = M / m[i];
            LL ai = red(a[i], m[i]); // 归一化到 [0, m[i])
            LL ti = mul(ai, inv(Mi, m[i]), m[i]);
            ans = (ans + i128(ti) * Mi) % M; // 恒有 ti*Mi < M, 安全
        }
        return ans;
    }
    // ---------- 方案 B：Garner ----------
    // 同一方程组, 求最小非负解 x 对 P 取模的结果 (P 任意, 无需与 m[i] 互质)
    // 全程不出现 Π m[i], 适合模数乘积爆 64 位的场合 (如合并多个 NTT 模数)
    LL garner(const vector<LL> &a, const vector<LL> &m, LL P) {
        const int n = (int)a.size();
        vector<LL> x(n); // 混合基数系数 x_i ∈ [0, m[i])
        for (int i = 0; i < n; i++) {
            x[i] = red(a[i], m[i]);
            for (int j = 0; j < i; j++) {
                LL inv = inv(m[j], m[i]); // m[j]^{-1} mod m[i]
                x[i] = mul(x[i] - x[j], inv, m[i]);
                if (x[i] < 0) x[i] += m[i];
            }
        }
        LL ans = 0, M = 1 % P; // M 是前缀乘积对 P 取模
        for (int i = 0; i < n; i++) {
            ans = (ans + i128(x[i]) * M) % P; // ans += x_i * Π_{k<i} m_k
            M = mul(M, m[i], P);
        }
        return ans;
    }
    // ---------- 方案 C：扩展 CRT（模数可不互质） ----------
    // x = a[i] (mod m[i]), 返回 {最小非负解, lcm}; 无解时返回 {0, 0}
    // 要求 m[i] > 0; lcm 不爆 long long
    pair<LL, LL> excrt(const vector<LL> &a, const vector<LL> &m) {
        const int n = (int)a.size();
        LL r = 0, M = 1; // 当前解 x = r (mod M)
        for (int i = 0; i < n; i++) {
            LL b = red(a[i], m[i]), x, y;
            LL g = exgcd(M, m[i], x, y); // M*x + m[i]*y = g
            LL d = b - r; // 需 M*t = b - r (mod m[i])
            if (d % g) return {0, 0}; // 无解
            LL n1 = m[i] / g; // 化简后模数
            LL t = mul(red(d / g, n1), red(x, n1), n1); // t = d/g * inv(M/g)
            r += M * t; // 新解
            M *= n1; // 新模数 = lcm
        }
        return {r, M};
    }
    void test() { // 自测
        // x = 2 (mod 3), x = 3 (mod 5), x = 2 (mod 7) | x == 23
        const LL x_crt = crt({2, 3, 2}, {3, 5, 7});
        assert(x_crt == 23ll);
        const LL x_garner = garner({2, 3, 2}, {3, 5, 7}, 1000000007LL);
        assert(x_garner == 23ll);
        // x = 2 (mod 6), x = 5 (mod 9) | x = 14 (mod 18)
        const auto [r, M] = excrt({2, 5}, {6, 9});
        assert(r == 14 && M == 18);
        // x = 2 (mod 6), x = 3 (mod 9) | 无解
        assert(excrt({2, 3}, {6, 9}).second == 0);
    }
}; // namespace CRT