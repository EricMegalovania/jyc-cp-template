constexpr int N = 5e5 + 5;
constexpr int mod = 998244353;
constexpr int inv3 = (mod + 1) / 3;
inline ll quickpow(ll a, int b = mod - 2){
	ll res = 1;
	while (b){
		if (b & 1)
			(res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}
namespace polynomial{
	int limit, len, rk[N];
	inline void init(int n){
		len = 0, limit = 1;
		while (limit < n){
			limit <<= 1;
			++len;
		}
		for (int i = 0; i < limit; ++i)
			rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
	}
	struct poly{
		vector<ll> dp;
		inline void resize(int n){
			dp.resize(n);
		}
		inline ll operator [](const int &x) const{
			return dp[x];
		}
		inline ll &operator [](const int &x){
			return dp[x];
		}
		inline int size() const{
			return (int)dp.size();
		}
		inline void print(){
			for (int i = 0; i < size(); ++i)
				cout << (dp[i] + mod) % mod << ' ';
			cout << '\n';
		}
		inline void NTT(){
			for (int i = 0; i < limit; ++i)
				if (i < rk[i])
					swap(dp[i], dp[rk[i]]);
			for (int mid = 1; mid < limit; mid <<= 1){
				ll gn = quickpow(3, (mod - 1) / (mid << 1));
				for (int i = 0; i < limit; i += mid << 1){
					ll g = 1;
					for (int j = 0; j < mid; ++j, (g *= gn) %= mod){
						ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
						dp[i + j] = (x + y) % mod;
						dp[i + j + mid] = (x - y) % mod;
					}
				}
			}
		}
		inline void INTT(){
			for (int i = 0; i < limit; ++i)
				if (i < rk[i])
					swap(dp[i], dp[rk[i]]);
			for (int mid = 1; mid < limit; mid <<= 1){
				ll gn = quickpow(inv3, (mod - 1) / (mid << 1));
				for (int i = 0; i < limit; i += mid << 1){
					ll g = 1;
					for (int j = 0; j < mid; ++j, (g *= gn) %= mod){
						ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
						dp[i + j] = (x + y) % mod;
						dp[i + j + mid] = (x - y) % mod;
					}
				}
			}
			ll inv = quickpow(limit);
			for (int i = 0; i < limit; ++i)
				(dp[i] *= inv) %= mod;
		}
		inline friend poly operator*(poly lhs, poly rhs){
			poly res;
			int up = lhs.size() + rhs.size() - 1;
			init(up);
			res.resize(limit);
			lhs.resize(limit), rhs.resize(limit);
			lhs.NTT(), rhs.NTT();
			for (int i = 0; i < limit; ++i)
				res.dp[i] = lhs.dp[i] * rhs.dp[i] % mod;
			res.INTT();
			res.resize(up);
			return res;
		}
		inline friend poly operator-(poly lhs, poly rhs){
			poly res;
			res.resize(max(lhs.size(), rhs.size()));
			lhs.resize(res.size()), rhs.resize(res.size());
			for (int i = 0; i < res.size(); ++i)
				res[i] = (lhs[i] - rhs[i]) % mod;
			return res;
		}
		inline friend poly operator+(poly lhs, poly rhs){
			poly res;
			res.resize(max(lhs.size(), rhs.size()));
			lhs.resize(res.size()), rhs.resize(res.size());
			for (int i = 0; i < res.size(); ++i)
				res[i] = (lhs[i] + rhs[i]) % mod;
			return res;
		}
		inline poly solve(int n){
			poly F, G;
			if (n == 1){
				F.dp.push_back(quickpow(dp[0]));
				return F;
			}
			F = solve((n + 1) / 2);
			G.resize(n);
			for (int i = 0; i < n; ++i)
				G.dp[i] = dp[i];
			init(n * 2);
			F.resize(limit), G.resize(limit);
			F.NTT(), G.NTT();
			for (int i = 0; i < limit; ++i)
				F[i] = (2 - F[i] * G[i] % mod) * F[i] % mod;
			F.INTT();
			F.resize(n);
			return F;
		}
		inline void reverse(){
			for (int i = 0; i * 2 < size(); ++i)
				swap(dp[i], dp[size() - i - 1]);
		}
		inline friend poly operator / (poly lhs, poly rhs){
			lhs.reverse(), rhs.reverse();
			int qwq = lhs.size() - rhs.size() + 1;
			rhs.resize(qwq);
			auto inv = rhs.solve(qwq);
			auto div = lhs * inv;
			div.resize(qwq);
			div.reverse();
			return div;
		}
		inline friend poly operator % (const poly &lhs, const poly &rhs){
			auto R = lhs - lhs / rhs * rhs;
			R.resize(rhs.size() - 1);
			return R;
		}
	};
};
using polynomial::poly;
