const int mod = 998244353;
inline LL inv(const LL& x) {
	assert(x != 0);
	LL res = 1, a = x % mod, b = mod - 2;
	while (b) {
		if (b & 1) (res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}
struct MI { //Mod-Int
	LL x, y; //x is val, y is zero's count
	MI(LL _x = 0, LL _y = 0): x(_x), y(_y) {}
	inline LL data() const {
		return y ? 0 : x;
	}
	inline MI operator*(const MI &rhs) const {
		return MI(x * rhs.x % mod, y + rhs.y);
	}
	inline MI operator+(const int &rhs) const {
		MI res = (*this);
		res.x = (data() + rhs) % mod;
		if (res.x == 0) res.x = res.y = 1;
		else res.y = 0;
		return res;
	}
	inline MI operator/(const MI &rhs) const {
		return MI(x * inv(rhs.x) % mod, y - rhs.y);
	}
	inline char* s() const { //for debug
		static char ss[100];
		sprintf(ss, "{%lld,%lld}", this->x, this->y);
		return ss;
	}
};
