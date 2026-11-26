#define s (*s_p)
template <class S>
struct SA {
    S *s_p;
    int n, m0;
    vector<int> rk, sa, h;

    // s 下标从 1 开始, m0 是字符集大小, s[1:] 值域必须要在 [1, m0] 中, s[0] = 0
    void init(S &_s, const int _m0) { // m0 一般取 128, 当然也可以取 26 之类的
        s_p = &_s;
        n = int(s.size()) - 1;
        m0 = _m0;
        init_sa_rk();
        init_h();
    }

    void init_sa_rk() {
        int m = m0, p;
        rk.assign(n * 2 + 1, 0);
        sa.assign(n + 1, 0);
        vector<int> rk_old(n * 2 + 1, 0);
        vector<int> id(n + 1, 0);
        vector<int> cnt(max(n, m) + 1, 0);

        // 长度 1: 初始基数排序
        for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;

        for (int w = 1;; w <<= 1, m = p) { // m = p 即为值域优化
            int cur = 0;
            for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
            for (int i = 1; i <= n; i++)
                if (sa[i] > w) id[++cur] = sa[i] - w;

            fill(cnt.begin(), cnt.begin() + m + 1, 0);
            for (int i = 1; i <= n; i++) cnt[rk[i]]++;
            for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];

            p = 0;
            swap(rk_old, rk);
            for (int i = 1; i <= n; i++) {
                if (rk_old[sa[i]] == rk_old[sa[i - 1]] &&
                    rk_old[sa[i] + w] == rk_old[sa[i - 1] + w])
                    rk[sa[i]] = p;
                else
                    rk[sa[i]] = ++p;
            }

            if (p == n) break; // p = n 时无需再排序
        }
    }

    void init_h() {
        h.assign(n + 1, 0);
        for (int i = 1, k = 0; i <= n; ++i) {
            if (k) --k;
            const int j = sa[rk[i] - 1];
            while (max(i, j) + k <= n && s[i + k] == s[j + k]) ++k;
            h[rk[i]] = k;
        }
    }
};
#undef s

struct Main {
    string s;
    SA<string> sa;
    void main() {
        cin >> s;
        s = char(0) + s;
        sa.init(s, 128);
        for (int i = 1; i < int(s.size()); ++i) {
            cout << sa.sa[i] << " \n"[i + 1 == int(s.size())];
        }
    }
};