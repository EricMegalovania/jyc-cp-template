// Fenwick<T>fen;
// 排列转中介数
void p2m(const vector<int>& a,const int& n,vector<int>& b){
	Fenwick<int>fen(n+1);
	b.resize(n+1);
	for(int i=n;i>0;--i){
		b[i]=fen.query(a[i]);
		fen.add(a[i],1);
	}
}

// 中介数转序号
LL m2id(const vector<int>& b,const int& n){
	LL res=0,base=1;
	for(int i=n-1;i>0;--i){
		base*=(n-i);
		res+=b[i]*base;
	}
	return res;
}

// 中介数转排列
void m2p(const vector<int>& b,const int& n,vector<int>& a){
	a.resize(n+1);
	Fenwick<int>fen(n+1);
	for(int i=1;i<=n;++i){
		fen.add(i,1);
	}
	for(int i=1,x;i<n;++i){
		x=fen.kth(b[i]+1);
		a[i]=x;
		fen.add(x,-1);
	}
	a[n]=fen.kth(1);
}
