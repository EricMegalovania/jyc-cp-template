#include <bits/stdc++.h>
#include <cassert>
using namespace std;

using Paths = vector<vector<int>>;

// 适用于所有奇数 n >= 7。
// 返回 n 个排列，每条有向边恰好作为相邻元素出现一次。
Paths construct(int n) {
    assert(n >= 7 && n % 2 == 1);

    if (n == 9) {
        return {
            {0, 1, 7, 2, 6, 3, 5, 4, 8},
            {3, 7, 4, 6, 5, 8, 1, 2, 0},
            {1, 4, 0, 5, 7, 6, 8, 2, 3},
            {6, 0, 7, 8, 3, 4, 2, 5, 1},
            {2, 7, 1, 0, 8, 4, 5, 3, 6},
            {7, 3, 0, 2, 1, 8, 5, 6, 4},
            {5, 0, 4, 1, 3, 2, 8, 6, 7},
            {4, 3, 8, 7, 0, 6, 1, 5, 2},
            {8, 0, 3, 1, 6, 2, 4, 7, 5}
        };
    }

    Paths ans;

    if (n % 4 == 3) {
        int k = (n - 3) / 4;
        int m = n - 1;
        int inf = m;
        vector<int> nxt(n, -1);

        for (int i = 0; i < m; ++i) {
            vector<int> c(n);
            c[0] = inf;

            for (int j = 1; j < n; ++j) {
                int d = (j % 2 == 0)
                      ? j / 2
                      : m - (j - 1) / 2;
                c[j] = (i + d) % m;
            }

            int p;
            if (i == 0)              p = 1;
            else if (i == k + 1)     p = 4 * k + 2;
            else if (i == 2 * k + 2) p = 3;
            else if (i == 3 * k + 2) p = 4 * k;
            else                     p = 2 * k;

            vector<int> a(n);
            for (int j = 0; j < n; ++j)
                a[j] = c[(p + j) % n];

            // 被切掉的边：路径终点 -> 路径起点。
            nxt[a.back()] = a.front();
            ans.push_back(std::move(a));
        }

        vector<int> last;
        int v = inf;
        for (int j = 0; j < n; ++j) {
            last.push_back(v);
            v = nxt[v];
        }
        ans.push_back(std::move(last));
        return ans;
    }

    int h = (n + 1) / 2;
    Paths old = construct(h);

    // 输入一个长度为 n+1 的圈，删去顶点 n。
    auto emit = [&](const vector<int>& c) {
        int p = int(find(c.begin(), c.end(), n) - c.begin());
        assert(p < n + 1);

        vector<int> a;
        for (int j = 1; j <= n; ++j)
            a.push_back(c[(p + j) % (n + 1)]);
        ans.push_back(std::move(a));
    };

    // 覆盖组内边，以及两组间的匹配边。
    for (const auto& a : old) {
        vector<int> c = a;
        for (int j = h - 1; j >= 0; --j)
            c.push_back(a[j] + h);
        emit(c);
    }

    // 覆盖两组间除去匹配的所有有向边。
    for (int i = 0; i < h - 1; ++i) {
        vector<int> q;

        for (int j = 0; j < h - 1; ++j) {
            int d = (j % 2 == 0)
                  ? j / 2
                  : h - 2 - (j - 1) / 2;
            int x = (i + d) % (h - 1);
            q.push_back(x + (j % 2 ? h : 0));
        }
        q.push_back(h - 1);

        vector<int> c = q;
        for (int x : q)
            c.push_back(x < h ? x + h : x - h);
        emit(c);
    }

    return ans;
}

void check(const Paths& a) {
    int n = int(a.size());
    vector<vector<int>> cnt(n, vector<int>(n));

    for (const auto& p : a) {
        assert(int(p.size()) == n);
        vector<int> seen(n);

        for (int v : p) {
            assert(0 <= v && v < n);
            assert(++seen[v] == 1);
        }

        for (int j = 1; j < n; ++j)
            ++cnt[p[j - 1]][p[j]];
    }

    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v)
            assert(cnt[u][v] == (u != v));

    printf("%d is OK.\n", n);
}

int main() {
    for(int n = 7; n <= 200; n += 2){
        auto a = construct(n);
        check(a);
    }
    return 0;
}
