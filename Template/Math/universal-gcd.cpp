#include <bits/stdc++.h>
using namespace std;
constexpr int N = 23;
constexpr int mod = 998244353;
typedef long long ll;
int n;
struct matrix {
	ll g[N][N];
	matrix() {
		memset(g, 0, sizeof(g));
	}
	matrix(int _n) {
		for (int i = 1; i <= _n; ++i)
			g[i][i] = 1;
	}
	inline matrix operator*(const matrix &rhs) const {
		matrix res;
		
		for (int i = 1; i <= n; ++i)
			for (int k = 1; k <= n; ++k)
				for (int j = 1; j <= n; ++j)
					(res.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
					
		return res;
	}
	inline matrix operator+(const matrix &rhs) const {
		matrix res = (*this);
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				(res.g[i][j] += rhs.g[i][j]) %= mod;
				
		return res;
	}
	inline void print() {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j)
				cout << g[i][j] << ' ';
				
			cout << '\n';
		}
	}
};
struct node {
	matrix x, y, xy;
	node(): x(n), y(n), xy() {}
	inline node operator*(const node &rhs) const {
		node res;
		res.x = x * rhs.x;
		res.y = y * rhs.y;
		res.xy = xy + x * rhs.xy * y;
		return res;
	}
	inline node operator^(ll rhs) const {
		node res, a = (*this);
		
		while (rhs) {
			if (rhs & 1)
				res = res * a;
				
			a = a * a;
			rhs >>= 1;
		}
		
		return res;
	}
};
inline node solve(ll p, ll q, ll r, ll l, node U, node R) {
	if (!n)
		return node();
		
	if (r >= q)
		return (U ^ (r / q)) * solve(p, q, l, r % q, U, R);
		
	if (p >= q)
		return solve(p % q, q, r, l, U, (U ^ (p / q)) * R);
		
	ll m = ((__int128)p * l + r) / q;
	
	if (!m)
		return R ^ l;
		
	return (R ^ ((q - r - 1) / p)) * U * solve(q, p, (q - r - 1) % p, m - 1, R, U)
	       * (R ^ (l - ((__int128) q * m - r - 1) / p));
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	ll p, q, r, l;
	cin >> p >> q >> r >> l >> n;
	node U, R;
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> R.x.g[i][j];
			
	R.xy = R.x;
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> U.y.g[i][j];
			
	solve(p, q, r, l, U, R).xy.print();
	return 0;
}
