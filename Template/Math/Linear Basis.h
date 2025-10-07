constexpr int K=64;
using ULL=unsigned long long;
class LB{ //linear-basis
private:
	array<ULL,K>a;
public:
	LB(){init();}
	void init(){
		fill(all(a),0);
	}
	void insert(ULL x){
		for(int i=K-1;i>=0;i--){
			if(!(x>>i)) continue;
			if(!a[i]){
				a[i]=x;
				break;
			}
			x^=a[i];
		}
	}
	bool find(ULL x){
		for(int i=K-1;i>=0;i--){
			if(!(x>>i)) continue;
			if(!a[i]) return 0;
			x^=a[i];
		}
		return 1;
	}
	ULL max(){
		ULL res=0;
		for(int i=K-1;i>=0;i--){
			if((res^a[i])>res) res^=a[i];
		}
		return res;
	}
	ULL min(){
		for(int i=0;i<K;i++){
			if(a[i]!=0) return a[i];
		}
		return 0;
	}
};
