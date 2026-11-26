namespace ST_C { // Sparse Table Constant
    int Logn[N];
    const bool init = []() -> bool {
        Logn[1] = 0, Logn[2] = 1;
        for (int i = 3; i < N; i++) Logn[i] = Logn[i / 2] + 1;
        return 1;
    }();
} // namespace ST_C
template <class S>
struct LCP : SA<S> { // SA for LCP
    using SA<S>::n, SA<S>::rk; // SA<S> 是依赖类型, 所以一定要加
    using VI = vector<int>;
    vector<VI> a;
    void init_st() { // remember to call !!!
        int mx_l = ST_C::Logn[n] + 1; // max log
        a.assign(mx_l, VI(n + 1, 0));
        a[0] = SA<S>::h;
        for (int j = 1; j < mx_l; j++) {
            int p = 1 << (j - 1);
            for (int i = 1; i + p <= n; i++)
                a[j][i] = min(a[j - 1][i], a[j - 1][i + p]);
        }
    }
    int lcp(int i, int j) const { // lcp(s[i:], s[j:]) | 1 <= i, j <= n
        if (i == j) return n - i + 1;
        int l = rk[i], r = rk[j];
        if (l > r) swap(l, r);
        ++l;
        int lt = r - l + 1;
        int p = ST_C::Logn[lt];
        return min(a[p][l], a[p][r - (1 << p) + 1]);
    }
};