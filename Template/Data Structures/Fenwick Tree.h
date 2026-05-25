template<typename T>
inline T __fen_add(const T x, const T y){ return x+y; }
template<typename T,auto op=__fen_add<T>,auto e=[](){ return T(0); }> // T is int or LL
struct Fenwick{
	int n,LOG;
	vector<T>c;
	inline int lowbit(const int& x){
		return x&(-x);
	}
	Fenwick(){}
	Fenwick(int n_){
		init(n_);
	}
	void init(int n_){
		c.assign(n=n_,e());
		LOG=bit_width((unsigned)n);
	}
	void add(int i,T x){
		for(;i<n;i+=lowbit(i)) c[i]=op(c[i],x);
	}
	T query(int i){
		T res=e();
		for(;i;i-=lowbit(i)) res=op(res,c[i]);
		return res;
	}
	int kth(T k){ // min p that sum(1,p)>=k
		int ans=0; T res=e();
		for(int i=LOG;~i;--i) {
			int nxt=ans+(1<<i);
			if(nxt<n && op(res,c[nxt])<k){
				res=op(res,c[nxt]);
				ans=nxt;
			}
		}
		return ans+1;
	}
};
