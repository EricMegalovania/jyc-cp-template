using M=vector<vector<Z>>;
vector<Z> mul(const M& a,vector<Z>& f,int n){ // a*f
	vector<Z>b(n);
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) b[i]+=a[i][j]*f[j];
	return b;
}
M mul(const M& a,M& b,int n){ // a*b
	vector c(n,vector<Z>(n));
	for(int k=0;k<n;k++) for(int i=0;i<n;i++) for(int j=0;j<n;j++){
		c[i][j]+=a[i][k]*b[k][j];
	}
	return c;
}

constexpr int N=[TODO]; // N is matrix size
constexpr int P=[TODO]; // assure (1<<P)>=n
M base[P]; vector<Z>base_f(N);

void init(){
	base[0]=M(N,vector<Z>(N));
	// [TODO], init base[0] and base_f
	for(int p=1;p<P;++p){
		base[p]=mul(base[p-1],base[p-1],N);
	}
}

Z calc(int n) {
	vector<Z>ans=base_f; --n;
	for(int p=0;n && p<P;++p,n>>=1){
		if(n&1) ans=mul(base[p],ans,N);
	}
	Z res; for(auto& v:ans) res+=v;
	return res;
}