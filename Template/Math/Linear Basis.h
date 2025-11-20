template<class S,int K>
class LB{ // linear-basis
private:
	static_assert(std::is_integral_v<S>);
	static_assert(K<=sizeof(S)*8);
	array<S,K>a;
public:
	LB(){ init(); }
	void init(){ fill(all(a),0); }
	void insert(S x){
		for(int i=K-1;i>=0;i--){
			if(!(x>>i)) continue;
			if(!a[i]){
				a[i]=x;
				break;
			}
			x^=a[i];
		}
	}
	bool find(S x){
		for(int i=K-1;i>=0;i--){
			if(!(x>>i)) continue;
			if(!a[i]) return 0;
			x^=a[i];
		}
		return 1;
	}
	S max() const{
		S res=0;
		for(int i=K-1;i>=0;i--){
			if((res^a[i])>res) res^=a[i];
		}
		return res;
	}
	S min() const{
		for(int i=0;i<K;i++){
			if(a[i]!=0) return a[i];
		}
		return 0;
	}
};
