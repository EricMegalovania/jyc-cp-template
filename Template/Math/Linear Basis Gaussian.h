template<class S,int K>
class LB{ // linear-gaussian-basis
private:
	static_assert(std::is_integral_v<S>);
	static_assert(K<=sizeof(S)*8);
	array<S,K>a; vector<S>dp;
	bool flag;
public:
	LB(){init();}
	void init(){
		fill(all(a),0);
		flag=0;
	}
	bool insert(S x){
		for(int k=K-1;~k;--k){
			if(!(x>>k)) continue;
			if(!a[k]){
				a[k]=x;
				adjust(k);
				flag=0;
				return 1;
			}
			x^=a[k];
		}
		return 0;
	}
	void adjust(int k){
		for(int i=k-1;~i;--i){
			if(a[i] && a[k]>>i&1){
				a[k]^=a[i];
			}
		}
		for(int i=K-1;i>k;--i){
			if(a[i] && a[i]>>k&1){
				a[i]^=a[k];
			}
		}
	}
	S max() const{
		S x=0;
		for(int i=K-1;~i;--i){
			x^=a[i];
		}
		return x;
	}
	void adjust(){
		if(flag) return;
		flag=1; dp.clear();
		for(int i=0;i<K;++i){
			if(a[i]) dp.emplace_back(a[i]);
		}
	}
	// 0-base, 0th=0, 1th=dp[0], 2th=dp[1], 3th=dp[0]^dp[1]
	S min_kth(S k){
		adjust();
		if(k>=(S(1)<<dp.size())){
			return -1;
		}
		S x=0;
		for(int i=0;i<dp.size();++i){
			if(k>>i&1) x^=dp[i];
		}
		return x;
	}
	S rank(S x){
		adjust(); S k=0;
		for(int i=dp.size()-1;~i;--i){
			int p=63-__builtin_clzll(dp[i]);
//			int p=31-__builtin_clz(dp[i]);
			if(x>>p&1){
				k+=S(1)<<i;
				x^=dp[i];
			}
		}
		if(x) return -1;
		return k;
	}
};
