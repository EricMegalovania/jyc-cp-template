//LCH 
#include <bits/stdc++.h>
using namespace std;
using line_t = long long;
struct Line{
	mutable line_t k, b, x;
	bool operator < (Line rhs)const{
		return k > rhs.k || k == rhs.k && b < rhs.b;
	}
	bool operator < (line_t rhs)const{
		return x < rhs;
	}
};
struct LCH : set<Line, less<> >{
	static const line_t sup = 1e6, inf = 0;
	long long floor(line_t x, line_t y){
		return x / y - ((x ^ y) < 0 && x % y);
	}
	bool over(iterator x, iterator y){
		if(y == end()){
			x->x = sup;
			return 0;
		}
		if(x->k == y->k) x->x = inf;
		else x->x = floor(y->b - x->b, x->k - y->k);
		return x->x >= y->x;
	}
	void add(Line v){
		auto z = insert(v).first, y = z++, x = y;
		while(over(y, z))
			z = erase(z);
		if(x == begin()) return;
		if(over(--x, y))
			over(x, erase(y));
		while((y = x) != begin() && (--x)->x >= y->x)
			over(x, erase(y));
	}
	line_t query(int x){
		auto it = lower_bound(x);
		return 1ll * it->k * x + it->b;
	}
};
