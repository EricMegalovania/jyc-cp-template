#include <bits/stdc++.h>
using namespace std;
using p_t = long double;
const p_t eps = 1e-9;
inline int sgn(p_t x) {
    return (x > eps) - (x < -eps);
}
struct P{
    p_t x, y;
    P(p_t x, p_t y): x(x), y(y){}
    P(): x(0), y(0){}
    inline P operator - (P rhs)const{
        return {x - rhs.x, y - rhs.y};
    }
    inline P operator + (P rhs) const{
        return {x + rhs.x, y + rhs.y};
    }
    inline P operator * (p_t k)const{
        return {x * k, y * k};
    }
    inline p_t operator ^ (P rhs)const{
        return x * rhs.y - rhs.x * y;
    }
    inline p_t operator * (P rhs)const{
        return x * rhs.x + y * rhs.y;
    }
    inline friend istream& operator >> (istream &in, P &rhs){
        return in >> rhs.x >> rhs.y;
    }
}p[200010], t[200010], c[5];
P e = {0, -1};
inline int cmp(P i, P j){
    p_t x = i ^ e, y = j ^ e;
    int a = x == 0 && i * e >= 0, b = y == 0 && j * e >= 0;
    if(a || b) return b - a;
    if(x == 0 || y == 0 || sgn(x) == sgn(y)) return sgn(i ^ j);
    return sgn(y - x);
}
struct L{
    P a, x;
    L(P a, P b): a(a), x(b - a){}
    L(): a(), x(){}
    inline P operator ^ (L rhs)const{
        return a - x * ((rhs.x ^ (a - rhs.a)) / (rhs.x ^ x));
    }
    inline bool operator < (L rhs)const{
        int o = cmp(x, rhs.x);
        if (o) return o > 0;
        return pos(rhs.a) < 0;
    }
    inline bool operator == (L rhs) const {
        return cmp(x, rhs.x) == 0;
    }
    inline void inv() {
        x = {-x.y, x.x};
    }
    inline int pos(P rhs)const{
        return sgn(x ^ rhs - a);
    }
}s[200010], q[200010];

int n;
p_t xl = -1e4, yl = -1e4, xr = 1e4, yr = 1e4;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	int m = 0;
	for(int i = 1; i <= n; i++){
		p_t a, b, c, d;
		cin >> a >> b >> c >> d;
		s[m++] = L(P(a, b), P(c, d));
	}
	for(int i = 0; i <= 4; i++)
		c[i] = {i == 1 || i == 2 ? xr : xl, i >> 1 & 1 ? yr : yl};
	for(int i = 0; i < 4; i++)
		s[m++] = {c[i], c[i + 1]};
	sort(s, s + m);
	
	int l = 0, r = 0;
	for (int i = 0; i < m; i++) {
		if (i && s[i] == s[i - 1]) continue;
		while (l + 1 < r && s[i].pos(t[r - 1]) <= 0) {
			r -= 1;
		}
		while (l + 1 < r && s[i].pos(t[l + 1]) <= 0) {
			l += 1;
		}
		q[r++] = s[i];
		if (l + 1 < r) {
			t[r - 1] = q[r - 2] ^ q[r - 1];
		}
	}
	while (l + 1 < r && q[l].pos(t[r - 1]) <= 0) {
		r -= 1;
	}
	t[l] = t[r] = q[r - 1] ^ q[l];
	
	p_t res = 0;
	for(int i = l + 1; i < r - 1; i++){
		res += (t[i] - t[r]) ^ (t[i + 1] - t[r]);
	}
	printf("%.3Lf\n", res / 2);
	return 0;
}
