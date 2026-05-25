template <class T, LL type> requires(type == 1 || type == T(1) / T(2))
void fwtxor(vector<T> &a, int _n = -1) {
    const int n = [&]() -> int {
        if (_n == -1) {
            const int ret = bit_ceil(a.size());
            a.resize(ret, T(0)); return ret;
        } else {
            assert((_n & (_n - 1)) == 0);
            assert(int(a.size()) >= _n);
            return _n;
        } }();
    for (int k = 1, x = 2; x <= n; k <<= 1, x <<= 1)
        for (int i = 0; i < n; i += x)
            for (int ij = i, j = 0; j < k; ++ij, ++j) {
                a[ij] += a[ij + k];
                a[ij + k] = a[ij] - a[ij + k] * 2;
                a[ij] *= type;
                a[ij + k] *= type;
            }
}