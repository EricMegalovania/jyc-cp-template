namespace ST_C{ //Sparse Table Constant
	int Logn[N];
	void init(){
		Logn[1]=0,Logn[2]=1;
		for (int i=3;i<N;i++) {
			Logn[i]=Logn[i/2]+1;
		}
	}
}
template<typename T,typename OP>
class ST{
	using VT=vector<T>;
	using VVT=vector<VT>;
	VVT a; OP op;
public:
	ST(){}
	ST(const vector<T> &v,int n,OP o):op(o){
		init(v,n); // v的有效下标为 1~n
	}
	void init(const vector<T> &v,int n){
		int mx_l=ST_C::Logn[n]+1; // max log
		a.assign(n+1,VT(mx_l,0));
		for(int i=1;i<=n;i++){
			a[i][0]=v[i];
		}
		for(int j=1;j<mx_l;j++){
			int p=(1<<(j-1));
			for(int i=1;i+p<=n;i++){
				a[i][j]=op(a[i][j-1],a[i+p][j-1]);
			}
		}
	}
	T query(int l,int r){
		int lt=r-l+1;
		int p=ST_C::Logn[lt];
		return op(a[l][p],a[r-(1<<p)+1][p]);
	}
};
struct MAXOP{
	template<typename T>
	T operator()(const T& x,const T& y){
		return max(x,y);
	}
};
struct MINOP{
	template<typename T>
	T operator()(const T& x,const T& y){
		return min(x,y);
	}
};

ST_C::init(); //初始化
