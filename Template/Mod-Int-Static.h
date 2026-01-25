#define D constexpr MI
#define C const
#define O operator
template<unsigned int mod>struct MI{
	D():v(0){}
	template<typename T>
	D(T x):v(x%mod){ if(v<0) v+=mod; }
	template<typename T>
	static D raw(T x){ MI z; z.v=x; return z; }
	D pow(LL n) C {
		MI x=*this, r=1;
		while(n){ if(n&1) r*=x; x*=x; n>>=1; }
		return r;
	}
	D inv() C { return pow(mod-2); }
	D& O +=(C MI& x){
		if((v+=x.v)>=mod) v-=mod;
		return *this;
	}
	D& O -=(C MI& x){
		if((v-=x.v)<0) v+=mod;
		return *this;
	}
	D& O *=(C MI& x){
		LL z=v; z*=x.v; v=z%mod;
		return *this;
	}
	D& O /=(C MI& x){ return *this=*this*x.inv(); }
	int val() C { return v; }
	static constexpr unsigned int umod(){ return mod; }
#define OP(s,t) friend D O s(C MI& x,C MI& y){ return MI(x) t y; }
	OP(+,+=) OP(-,-=) OP(*,*=) OP(/,/=)
#undef OP
private:
	int v;
};
#undef D
#undef C
#undef O

using Z=MI<TODO>;
#define raw(x) Z::raw(x)