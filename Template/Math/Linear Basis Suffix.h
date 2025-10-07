constexpr int K=20;
constexpr int inf=1e9;
struct SLB{ // suffix-linear-basis
	array<int,K>a,t;
	SLB(){init();}
	void init(){
		fill(all(a),0);
		fill(all(t),inf);
	}
	// Insert vector x at time i.
	void insert(int x,int i){
		for(int k=K-1;~k && x;--k){
			if(!(x>>k)) continue;
			if(i<t[k]){
				swap(a[k],x);
				swap(t[k],i);
			}
			x^=a[k];
		}
	}
	// Find max xor of time <=i
	int query(int i) const {
		int x=0;
		for(int k=K-1;~k;--k){
			if(t[k]<=i && (x^a[k])>x){
				x^=a[k];
			}
		}
		return x;
	}
	vector<int> get() const {
		vector<int>o;
		for(int i=0;i<K;++i){
			if(a[i] && t[i]!=inf){
				o.push_back(t[i]);
			}
		}
		sort(all(o));
		return o;
	}
};
