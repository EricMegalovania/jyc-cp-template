const int K=64;
using ULL=unsigned long long;
class LB{ //linear-gaussian-basis
private:
	array<ULL,K>a;
	vector<ULL>dp;
	bool flag;
public:
	LB(){init();}
	void init(){
		fill(all(a),0);
		flag=0;
	}
	bool insert(ULL x){
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
	ULL max() const{
		ULL x=0;
		for(int i=K-1;~i;--i){
			x^=a[i];
		}
		return x;
	}
	void adjust(){
		if(flag) return;
		flag=1;
		clr(dp);
		for(int i=0;i<K;++i){
			if(a[i]) dp.push_back(a[i]);
		}
	}
	// 0-base, 0th=0, 1th=dp[0], 2th=dp[1], 3th=dp[0]^dp[1]
	ULL min_kth(ULL k){
		adjust();
		if(k>=((ULL)(1)<<dp.size())){
			return -1;
		}
		ULL x=0;
		for(int i=0;i<dp.size();++i){
			if(k>>i&1) x^=dp[i];
		}
		return x;
	}
	ULL rank(ULL x){
		adjust();
		ULL k=0;
		for(int i=dp.size()-1;~i;--i){
			int p=63-__builtin_clzll(dp[i]);
//			int p=31-__builtin_clz(dp[i]);
			if(x>>p&1){
				k+=(ULL)(1)<<i;
				x^=dp[i];
			}
		}
		if(x) return -1;
		return k;
	}
	void get(){
		adjust();
		vector<ULL>pt;
		auto dfs=[&](auto&& self,int u,ULL x)->void{
			if(u==dp.size()){
				pt.push_back(x);
				return;
			}
			self(self,u+1,x);
			self(self,u+1,x^dp[u]);
		};
		dfs(dfs,0,ULL(0));
		sort(all(pt));
		for(ULL i=0;i<pt.size();++i){
			debug("rk=%llu | x=%llu\n",i,pt[i]);
		}
	}
	void check() const{
		for(int i=K-1;~i;--i){
			for(int j=i-1;~j;--j){
				if(a[i]>>j&1){
					assert((a[i]^a[j])==a[i]);
				}
			}
		}
	}
	void print() const{
		for(int i=K-1;~i;--i){
			for(int j=K-1;~j;--j){
				debug("%d",(int)(a[i]>>j&1));
			}
			debug("\n");
		}
	}
};
