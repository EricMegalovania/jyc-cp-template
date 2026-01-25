#define C const
#define ui unsigned int
#define ull unsigned long long
struct barrett{
	ui m; ull im;
	explicit barrett(ui _m):m(_m),im((ull)(-1)/_m+1){}
	ui umod() C { return m; }
	ui red(C LL& x) C {
		bool neg=0; ull ux;
		if(x<0){
			neg=1;
			if(x==LLONG_MIN) ux=(1ull<<63);
			else ux=(ull)(-x);
		}
		else ux=(ull)(x);
		ui r=redu(ux);
		if(neg){
			if(!r) return 0;
			else return m-r;
		}
		return (ui)r;
	}
	ui redu(const ull& z) C {
		ull x=(ull)(((__uint128_t)(z)*im)>>64);
		ull y=x*m;
		return (ui)(z-y+(z<y?m:0));
	}
	ui mul(ui a, ui b) C {
		ull z=a; z*=b;
		return redu(z);
	}
};
#undef ull

#define D constexpr MI
#define O operator
template<int id>struct MI{
	D():v(0){}
	template<typename T>
	D(T x):v(bt.red(x)){ if(v<0) v+=mod(); }
	template<typename T>
	static D raw(T x){ MI z; z.v=x; return z; }
	static void set_mod(ui m){ bt=barrett(m); }
	D pow(LL n) C {
		MI x=*this, r=1;
		while(n){if(n&1) r*=x; x*=x; n>>=1;}
		return r;
	}
	D inv() C { return pow(mod()-2); }
	D& O +=(C MI& x){
		if((v+=x.v)>=mod()) v-=mod();
		return *this;
	}
	D& O -=(C MI& x){
		if((v-=x.v)<0) v+=mod();
		return *this;
	}
	D& O *=(C MI& x){
		v=bt.mul(v,x.v);
		return *this;
	}
	D& O /=(C MI& x){
		return *this=*this*x.inv();
	}
	int val() C{ return v; }
	static ui mod(){ return bt.umod(); }
	static ui umod(){ return bt.umod(); }
#define OP(s,t) friend D O s(C MI& x,C MI& y){return MI(x) t y;}
	OP(+,+=) OP(-,-=) OP(*,*=) OP(/,/=)
#undef OP
private:
	int v;
	static barrett bt;
};
template<int id>barrett MI<id>::bt(998244353);
#undef D
#undef C
#undef O
#undef ui

using Z=MI<0>;
#define raw(x) Z::raw(x)

Z::set_mod(TODO);