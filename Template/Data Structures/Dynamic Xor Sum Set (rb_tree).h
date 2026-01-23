// #include<template/rb_tree>
template<class S,int K>
requires (is_integral_v<S> && K<=sizeof(S)*8)
struct xorsum{ // a set, no duplicate element
private:
	array<rb_tree<S>,K+1>dp{};
public:
	void modify(const S x){
		for(int p=0;p<=K;++p){
			auto&& s=dp[p];
			const S y=x&((S(1)<<(p+1))-1);
			auto it=s.find(y);
			if(it==s.end()) s.insert(y);
			else s.erase(it);
		}
	}
	S query(const S x){
		S r=S(0);
		for(int p=0;p<=K;++p){
			if(dp[p].empty()) continue;
			const S lim=S(1)<<(p+1);
			const S xx=x&(lim-1);
			const S R=lim-xx;
			auto [f,L]=[&]()->pair<bool,S> {
				S L=lim/2-xx;
				if(L<0) return {dp[p].size()&1,L+lim};
				else return {0,L};
			}();
			f^=(dp[p].order_of_key(L)&1);
			f^=(dp[p].order_of_key(R)&1);
			if(f) r|=lim;
		}
		return r>>1;
	}
};