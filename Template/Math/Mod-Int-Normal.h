#define D constexpr
#define C const
#define O operator
struct Z{
	static D int mod=TODO;
	D Z():v(0){}
	template<typename T>
	D Z(T x):v(x%mod){if(v<0) v+=mod;}
	template<typename T>
	static D Z raw(T x){Z z; z.v=x; return z;}
	D Z pow(LL n) C {
		Z x=*this, r=1;
		while(n){if(n&1) r*=x; x*=x; n>>=1;}
		return r;
	}
	D Z inv() C {return pow(mod-2);}
	Z& O+=(C Z& x){
		if((v+=x.v)>=mod) v-=mod;
		return *this;
	}
	Z& O-=(C Z& x){
		if((v-=x.v)<0) v+=mod;
		return *this;
	}
	Z& O *=(C Z& x){
		LL z=v; z*=x.v; v=z%mod;
		return *this;
	}
	Z& O /=(C Z& x){
		return *this=*this*x.inv();
	}
	int val() C{return v;}
#define OP(s,t) friend Z O s(C Z& x,C Z& y){return Z(x) t y;}
	OP(+,+=) OP(-,-=) OP(*,*=) OP(/,/=)
#undef OP
private:
	int v;
};
#undef D
#undef C
#undef O
