#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include <local/dbg.h>
#else
    #define dbg(...) 42
#endif

using LL = long long;

// clang-format off
#define ai(x) using ai##x = array<int, x>;
ai(2); ai(3); ai(4); ai(5); ai(6); ai(7); ai(8); ai(9); ai(10); ai(26);
#undef ai
// clang-format on

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
template <class T>
inline bool updmx(T &x, const T &y) { return x < y ? x = y, 1 : 0; }
template <class T>
inline bool updmn(T &x, const T &y) { return y < x ? x = y, 1 : 0; }
template <class T>
inline void clr(T &x) { T().swap(x); }

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
LL rand(LL l, LL r) { return rng() % (r - l + 1) + l; }

namespace FMF { // find-max-factor
    using big = __int128_t;
    LL gcd(LL a, LL b) {
        return b ? gcd(b, a % b) : a;
    }
    LL ksm(LL a, LL b, LL p) {
        a %= p;
        LL res = 1;
        while (b) {
            if (b & 1) res = (big)res * a % p;
            a = (big)a * a % p;
            b >>= 1;
        }
        return res;
    }
    bool Miller_Rabin(LL p) { // 判断素数
        if (p < 2) return 0;
        if (p == 2 || p == 3 || p == 5 || p == 7 || p == 43) return 1;
        LL d = p - 1, r = 0;
        while (!(d & 1)) ++r, d >>= 1; // 将d处理为奇数
        for (LL k = 0; k < 10; k++) {
            LL a = rng() % (p - 2) + 2;
            LL x = ksm(a, d, p);
            if (x == 1 || x == p - 1) continue;
            for (int i = 0; i < r - 1; i++) {
                x = (big)x * x % p;
                if (x == p - 1) break;
            }
            if (x != p - 1) return 0;
        }
        return 1;
    }
    LL Pollard_Rho(LL x) {
        LL s = 0, t = 0, c = rng() % (x - 1) + 1;
        int step = 0, goal = 1;
        LL val = 1;
        for (goal = 1;; goal <<= 1, s = t, val = 1) { // 倍增优化
            for (step = 1; step <= goal; step++) {
                t = ((big)t * t + c) % x;
                val = (big)val * abs(t - s) % x;
                if ((step % 127) == 0) {
                    LL d = gcd(val, x);
                    if (d > 1) return d;
                }
            }
            LL d = gcd(val, x);
            if (d > 1) return d;
        }
    }
    LL max_factor;
    void fac(LL x) {
        if (x <= max_factor || x < 2) return;
        if (Miller_Rabin(x)) { // 如果x为质数
            max_factor = max(max_factor, x); // 更新答案
            return;
        }
        LL p = x;
        while (p >= x) p = Pollard_Rho(x); // 使用该算法
        while ((x % p) == 0) x /= p;
        fac(x), fac(p); // 继续向下分解x和p
    }
} // namespace FMF

int main() {
    freopen("Hash.py", "w", stdout);
    constexpr LL base = 1e18;
    vector<int> off(500);
    for (int i = 0, x = 0; i < int(off.size()); ++i) {
        while (1) {
            FMF::fac(base + x);
            if (FMF::max_factor == (base + x)) {
                off[i] = x++;
                break;
            } else {
                ++x;
            }
        }
    }
    cout << "sub = ord('a') - 1\n";
    cout << "FUCK_YOU = [" << off[0];
    for (auto x : off | views::drop(1)) {
        cout << ", " << x;
    }
    cout << "]  # nopep8\n";
    cout << "MOD = 10**18 + FUCK_YOU[random.randint(0, len(FUCK_YOU) - 1)]\n";
    cout << "P = 13331\n";
    return 0;
}