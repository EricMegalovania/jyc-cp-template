template<typename T> // T is int or LL
struct Fenwick{
	int n,LOG;
	vector<T>c;
	inline int lowbit(const int& x){
		return x&(-x);
	}
	Fenwick(int n_){
		init(n_);
	}
	void init(int n_){
		c.assign(n=n_,T(0));
		LOG=__lg(n)+1;
	}
	void add(int i,T x){
		for(;i<n;i+=lowbit(i)) c[i]+=x;
	}
	T query(int i){
		T res=0;
		for(;i;i-=lowbit(i)) res+=c[i];
		return res;
	}
	int kth(T k){ // min p that sum(1,p)>=k
		int ans=0; T cnt=0;
		for(int i=LOG;~i;--i) {
			int nxt=ans+(1<<i);
			if(nxt<n && cnt+c[nxt]<k){
				cnt+=c[nxt];
				ans=nxt;
			}
		}
		return ans+1;
	}
};
