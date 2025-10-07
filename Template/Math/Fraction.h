#define N 1024
LL tab[N][N];
void init(){
	for(int i=0;i<N;++i){
		tab[0][i]=tab[i][0]=tab[i][i]=i;
		tab[1][i]=tab[i][1]=1;
	}
	for(int i=3;i<N;++i){
		for(int j=2;j<i;++j){
			tab[i][j]=tab[j][i]=tab[j][i%j];
		}
	}
}
LL gc(LL x,LL y){
	if(x<N && y<N) return tab[x][y];
	return y?gc(y,x%y):x;
}
struct frac{ //fraction
	LL a,b; // a/b
	void adjust(){
		if(!a) b=1;
		else{
			bool f=0;
			if(a<0) a=-a,f=1;
			if(b<0) b=-b,f^=1;
			LL g=gc(a,b);
			a/=g,b/=g;
			if(f) a=-a;
		}
	}
	friend bool operator <(const frac& A,const frac& B){
		LL l=A.b/gc(A.b,B.b)*B.b;
		return A.a*(l/A.b)<B.a*(l/B.b);
	}
	friend bool operator ==(const frac& A,const frac& B){
		return A.a==B.a && A.b==B.b;
	}
	friend frac operator +(const frac& A,const frac& B){
		frac res;
		res.b=A.b/gc(A.b,B.b)*B.b;
		res.a=A.a*(res.b/A.b)+B.a*(res.b/B.b);
		res.adjust();
		return res;
	}
	friend frac operator *(const frac& A,const frac& B){
		frac res{A.a*B.a,A.b*B.b};
		res.adjust();
		return res;
	}
};

init();
