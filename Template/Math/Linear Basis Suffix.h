constexpr int inf=1e9;
template<class S,int K>
struct SLB{ // suffix-linear-basis
	static_assert(std::is_integral_v<S>);
	static_assert(K<=sizeof(S)*8);
	array<S,K>a; array<int,K>t;
	SLB(){ init(); }
	void init(){
		fill(all(a),0);
		fill(all(t),inf);
	}
	// Insert vector x at time i.
	void insert(S x,int i){
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
	S query(int i) const {
		S x=0;
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
				o.emplace_back(t[i]);
			}
		}
		sort(all(o));
		return o;
	}
};
