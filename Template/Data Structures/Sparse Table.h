namespace ST_C { // Sparse Table Constant
    int Logn[N];
    const bool init = []() -> bool {
        Logn[1] = 0, Logn[2] = 1;
        for (int i = 3; i < N; i++) Logn[i] = Logn[i / 2] + 1;
        return 1;
    }();
} // namespace ST_C
template <class T, auto op>
struct ST {
    using VT = vector<T>;
    vector<VT> a;
    ST() {}
    ST(const VT &v, int n) { init(v, n); } // v is 1-index
    void init(const VT &v, int n) {
        int mx_l = ST_C::Logn[n] + 1; // max log
        a.assign(mx_l, VT(n + 1, 0));
        for (int i = 1; i <= n; ++i) a[0][i] = v[i];
        for (int j = 1; j < mx_l; ++j) {
            int p = 1 << (j - 1);
            for (int i = 1; i + p <= n; ++i)
                a[j][i] = op(a[j - 1][i], a[j - 1][i + p]);
        }
    }
    T query(int l, int r) const {
        int lt = r - l + 1;
        int p = ST_C::Logn[lt];
        return op(a[p][l], a[p][r - (1 << p) + 1]);
    }
};
int op(int x, int y) { return max(x, y); }

ST<int, op> st(a, n); // usage
