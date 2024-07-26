LL gcd(LL x,LL y){return y?gcd(y,x%y):x;}
struct frac{ //fraction
	LL a,b; // a/b
	friend bool operator <(const frac& A,const frac& B){
		LL l=A.b/gcd(A.b,B.b)*B.b;
		return A.a*(l/A.b)<B.a*(l/B.b);
	}
	friend frac operator +(const frac& A,const frac& B){
		frac res;
		res.b=A.b/gcd(A.b,B.b)*B.b;
		res.a=A.a*(res.b/A.b)+B.a*(res.b/B.b);
		if(!res.a) return {0,1};
		LL g=gcd(res.a,res.b);
		res.a/=g,res.b/=g;
		return res;
	}
};
