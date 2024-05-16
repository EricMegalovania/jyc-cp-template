template<typename T>//T is int or LL
class FenTree{
private:
	int n;
	vector<T>c;
	inline int lowbit(const int& x){
		return x&(-x);
	}
public:
	FenTree(int n_){
		init(n_);
	}
	void init(int n_){
		c.assign(n=n_,T(0));
	}
	void add(int i,int x){
		for(;i<n;i+=lowbit(i)) c[i]+=x;
	}
	T query(int i){
		T res=0;
		for(;i;i-=lowbit(i)) res+=c[i];
		return res;
	}
};
