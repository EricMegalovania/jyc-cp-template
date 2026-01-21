struct FenwickBool{
	FenwickBool(){}
	FenwickBool(int n_){ init(n_); }
	void init(int n_){ // [0,n_) but store with [1,n_]
		c.assign(n=n_+1,false);
		in.assign(n,false);
		sz=0;
	}
	void modify(int i){
		if(!in[++i]) ++sz;
		else --sz;
		in[i]=in[i]^1;
		for(;i<n;i+=lowbit(i)) c[i]=c[i]^1;
	}
	bool query(int i){
		bool r=0;
		for(++i;i;i-=lowbit(i)) r^=c[i];
		return r;
	}
	size_t size(){ return sz; }
	bool empty(){ return !sz; }
private:
	inline int lowbit(const int& x){ return x&(-x); }
	int n; size_t sz; vector<bool>c,in;
};

template<class S,int K,bool ins_and_del=false>
requires (is_integral_v<S> && K<=sizeof(S)*8 && K<=20)
struct xorsum{ // a set, no duplicate element
private:
	conditional_t<ins_and_del,set<S>,monostate>a;
	array<FenwickBool,K+1>dp{};
public:
	xorsum(){
		for(int p=0;p<=K;++p){
			dp[p].init(1<<(p+1));
		}
	}
	// op | -1:erase 0:modify 1:insert
	// ret | 1:op ok 0:op fail
	template<int op=0> requires (-1<=op && op<=1)
	bool modify(const S x){
		if constexpr (ins_and_del){
			bool sig=[&]()->bool {
				auto it=a.find(x);
				if(it==a.end()){
					if constexpr (op==-1) return 0; // erase fail
					else a.insert(x);
				}
				else{
					if constexpr (op==1) return 0; // insert fail
					else a.erase(x);
				}
				return 1;
			}();
			if(!sig) return 0;
		}
		for(int p=0;p<=K;++p){
			const S lim=S(1)<<(p+1);
			dp[p].modify(x&(lim-1));
		}
		return 1;
	}
	template<bool T=ins_and_del,typename=std::enable_if_t<T>>
	bool insert(const S x){ return modify<1>(x); }
	template<bool T=ins_and_del,typename=std::enable_if_t<T>>
	bool erase(const S x){ return modify<-1>(x); }
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
			f^=dp[p].query(L-1); // < L
			f^=dp[p].query(R-1); // < R
			if(f) r|=lim;
		}
		return r>>1;
	}
};