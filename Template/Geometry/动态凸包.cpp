//动态凸包
#include <bits/stdc++.h>
using namespace std;
using p_t = int;
using p_t2 = long long;
struct P{
	mutable p_t x, y;
	P operator - (P b)const{
		return {x - b.x, y - b.y};
	}
	p_t2 operator ^ (P b)const{
		return (p_t2)x * b.y - (p_t2)y * b.x;
	}
	bool operator < (P b)const{
		return x < b.x;
	}
	bool operator < (p_t b)const{
		return x < b;
	}
};
int sgn(p_t2 x){
	return (x > 0) - (x < 0);
}
struct HULL:set<P, less<> >{//��͹�� 
	int out(P v){
		auto it = lower_bound(v.x);
		if(it == end()) return 1;
		if(it->x == v.x) return sgn(v.y - it->y);
		if(it == begin()) return 1;
		auto p = prev(it);
		return sgn(*p - v ^ *it - v);
	}
	void add(P v){
		if(out(v) <= 0) return;
		auto it = find(v);
		if(it != end()) it->y = v.y;
		else it = insert(v).first;
		auto p = next(it);
		if(p != end()){
			auto nxt = next(p);
			while(nxt != end()){
				if(sgn(*it - *p ^ *nxt - *p) > 0) break;
				p = erase(p); nxt = next(p);
			}
		}
		if(it != begin()){
			p = prev(it);
			while(p != begin()){
				auto pre = prev(p);
				if(sgn(*pre - *p ^ *it - *p) > 0) break;
				erase(p); p = prev(it);
			}
		}
	}
}hull[2];
int main(){
	int q;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> q;
	while(q--){
		int op, x, y;
		cin >> op >> x >> y;
		if(op == 1) hull[0].add({x, y}), hull[1].add({x, -y});
		else printf(hull[0].out({x, y}) <= 0 && hull[1].out({x, -y}) <= 0 ? "YES\n" : "NO\n");
	}
	return 0;
}
