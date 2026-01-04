// Mod-Int-Dynamic
// NTT-Primitive-Root
template<class Z>
struct PM : public vector<Z>{  // DO NOT USE POINTER !!
	using vector<Z>::vector;
	static inline unsigned int mo=-1;
	static inline Z g=-1,gi=-1;
	static Z get_g(){
		if (mo==167772161 || mo==469762049 || mo==998244353 || mo==1004535809){
			return Z::raw(3);
		}
		else if (mo==(int)(1e9+7)) return Z::raw(5);
		else if (mo==754974721) return Z::raw(11);
		else return prim_root<>(mo);
	}
	static void set_mod(const unsigned int mod){
		Z::set_mod(mod);
		mo=Z::umod();
		g=get_g();
		gi=g.inv();
	}
	static inline int last=-1,lim=-1,L=-1;
	static inline vector<int> r{}; // butterfly transform
	static constexpr void init(const int d){
		int l=1,lg=0;
		if(d<=1) l=1,lg=0;
		else{
			l=d-1; l|=l>>1; l|=l>>2;
			l|=l>>4; l|=l>>8; l|=l>>16;
			lg=31-__builtin_clz(++l);
		}
		if(l==last) return;
		lim=l,L=lg;
		r.assign(lim,0);
		for(int i=0;i<lim;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(L-1));
		}
	}
	template<int type>
	void ntt(){
		#define a (*this)
		for(int i=0;i<lim;i++){
			if(i<r[i]) swap(a[i],a[r[i]]);
		}
		for(int mid=1;mid<lim;mid<<=1){
			const Z Wn=[&]()->Z {
				if constexpr(type==1) return g.pow((mo-1)/(mid<<1));
				else return gi.pow((mo-1)/(mid<<1));
			}();
			for(int j=0;j<lim;j+=(mid<<1)){
				Z w=Z::raw(1);
				for(int k=0;k<mid;++k,w*=Wn){
					const Z x=a[j+k];
					const Z y=w*a[j+k+mid];
					a[j+k]+=y;
					a[j+k+mid]=x-y;
				}
			}
		}
		if constexpr(type==-1){
			const Z inv=Z(lim).inv();
			for(int i=0;i<lim;i++) a[i]*=inv;
		}
		#undef a
	}
	PM& operator *=(PM b){
		#define a (*this)
		const int n=(int)(a.size())-1;
		const int m=(int)(b.size())-1;
		if(min(n,m)<=64){
			PM c(n+m+1);
			for(int i=0;i<=n;++i){
				for(int j=0;j<=m;++j){
					c[i+j]+=a[i]*b[j];
				}
			}
			swap(a,c);
			return a;
		}
		init(n+m);
		a.resize(lim); a.ntt<1>();
		b.resize(lim); b.ntt<1>();
		for(int i=0;i<lim;++i) a[i]*=b[i];
		a.ntt<-1>();
		a.resize(n+m+1);
		return a;
		#undef a
	}
	friend PM operator *(PM a,PM b){ return a*=b; }
};

// c[(i*j)%P]+=a[i]*b[j]%mod;
template<class Poly>
Poly conv(const Poly& a,const Poly& b,const int P,const int g){  // g is pr of P
	Poly aa(P-1),bb(P-1);
	for(int i=0,x=1;i<P-1;++i){
		aa[i]=a[x];
		bb[i]=b[x];
		x=x*g%P;
	}
	aa*=bb;
	for(int i=P-1;i<(int)(aa.size());++i){
		int j=i%(P-1);
		aa[j]+=aa[i];
	}
	Poly c(P);
	for(int i=0,x=1;i<P-1;++i){
		c[x]=aa[i];
		x=x*g%P;
	}
	return c;
}

using Z=MI<0>;
#define raw(x) Z::raw(x)
using Poly=PM<Z>;

Poly::set_mod(TODO);