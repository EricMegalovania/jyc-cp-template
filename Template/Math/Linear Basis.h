using ULL=unsigned long long;
class LB{ //linear-basis
private:
	array<ULL,64>a;
public:
	LB(){init();}
	void init(){
		fill(all(a),0);
	}
	void insert(ULL x){
		for(int i=63;i>=0;i--){
			if(!(x>>i)) continue;
			if(!a[i]){
				a[i]=x;
				break;
			}
			x^=a[i];
		}
	}
	bool find(ULL x){
		for(int i=63;i>=0;i--){
			if(!(x>>i)) continue;
			if(!a[i]) return 0;
			x^=a[i];
		}
		return 1;
	}
	ULL max(){
		ULL res=a[63];
		for(int i=62;i>=0;i--){
			if((res^a[i])>res) res^=a[i];
		}
		return res;
	}
	ULL min(){
		for(int i=0;i<=63;i++){
			if(a[i]!=0) return a[i];
		}
		return 0;
	}
};
