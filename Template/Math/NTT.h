bool notP[N],haspr[N]; int phi[N],mn_p[N];
vector<int>prime;
void init_prime(const int& n=N){ // init [1,n-1]
	haspr[2]=haspr[4]=phi[1]=mn_p[1]=notP[1]=1;
	for(int i=2;i<n;i++){
		if(!notP[i]){
			prime.push_back(mn_p[i]=i);
			phi[i]=i-1;
		}
		for(const int& p:prime){
			if(i>(n-1)/p) break;
			notP[i*p]=1,mn_p[i*p]=p;
			if(i%p==0){
				phi[i*p]=phi[i]*p;
				break;
			}
			phi[i*p]=phi[i]*(p-1);
		}
	}
	for(int i=1;i<prime.size();++i){
		int p=prime[i];
		for(LL j=p;j<N;j*=p) haspr[j]=1;
		for(LL j=2*p;j<N;j*=p) haspr[j]=1;
	}
}

LL qpow(LL a,LL b,LL p){
	a%=p; LL r=1;
	while(b){
		if(b&1) r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}

// Primitive-Root, can change to vector<int>
#ifdef ALLPR
bool cop[N],ispr[N];
vector<int>prim_root(int n){
	if(!haspr[n]) return {};
	if(n==2 || n==4) return {n-1};
	int tmp=phi[n];
	vector<int>d;
	for(auto& p:prime){
		if(p*p>tmp) break;
		if(tmp%p==0){
			d.push_back(p);
			do{tmp/=p;}while(tmp%p==0);
			for(int j=p;j<phi[n];j+=p) cop[j]=1;
		}
	}
	if(tmp>1){
		d.push_back(tmp);
		for(int i=tmp;i<phi[n];i+=tmp) cop[i]=1;
	}
	int mnpr=1;
	for(;;++mnpr){
		for(;__gcd(mnpr,n)!=1;++mnpr);
		int j=0;
		for(;j<d.size() && qpow(mnpr,phi[n]/d[j],n)!=1;++j);
		if(j>=d.size()) break;
	}
	tmp=mnpr;
	for(int i=1;i<phi[n];++i,tmp=tmp*mnpr%n){
		if(!cop[i]) ispr[tmp]=1;
		else cop[i]=0;
	}
	vector<int>vec;
	for(int i=1;i<n;++i){
		if(ispr[i]){
			ispr[i]=0;
			vec.push_back(i);
		}
	}
	return vec;
}
#else
int prim_root(int n){
	if(!haspr[n]) return 0;
	if(n==2 || n==4) return n-1;
	int tmp=phi[n];
	vector<int>d;
	for(auto& p:prime){
		if(p*p>tmp) break;
		if(tmp%p==0){
			d.push_back(p);
			do{tmp/=p;}while(tmp%p==0);
		}
	}
	if(tmp>1) d.push_back(tmp);
	int mnpr=1;
	for(;;++mnpr){
		for(;__gcd(mnpr,n)!=1;++mnpr);
		int j=0;
		for(;j<d.size() && qpow(mnpr,phi[n]/d[j],n)!=1;++j);
		if(j>=d.size()) break;
	}
	return mnpr;
}
#endif

using Poly=vector<LL>;
namespace NTT{
	int lim,L,last=-1;
	// modify if mod is constexpr
	int g,gi; // pr, pr_inv
	int mo=-1;
	vector<int>r;
	inline void ADD(LL& x,const LL& y){
		if((x+=y)>=mo) x-=mo;
	}
	void NTT(vector<LL>& a,int type){
		for(int i=0;i<lim;i++){
			if(i<r[i]) swap(a[i],a[r[i]]);
		}
		for(int mid=1;mid<lim;mid<<=1){
			// modify if mod is constexpr
			LL Wn=qpow(type==1?g:gi,(mo-1)/(mid<<1),mo);
			for(int j=0;j<lim;j+=(mid<<1)){
				LL w=1;
				for(int k=0;k<mid;k++,w=(w*Wn)%mo){
					LL x=a[j+k];
					LL y=w*a[j+k+mid]%mo;
					ADD(a[j+k],y);
					a[j+k+mid]=mo-y;
					ADD(a[j+k+mid],x);
				}
			}
		}
		if(type==-1){
			// modify if mod is constexpr
			LL inv=qpow(lim,mo-2,mo);
			for(int i=0;i<lim;i++){
				a[i]=(a[i]*inv)%mo;
			}
		}
	}
	void init_mod(const int& m){
		if(mo==m) return;
		mo=m;
		if(mo==167772161 || mo==469762049 ||
			mo==998244353 || mo==1004535809) g=3;
		else if(mo==(int)(1e9+7)) g=5;
		else if(mo==754974721) g=11;
		else g=prim_root(mo);
		gi=qpow(g,mo-2,mo);
	}
	void init(int d){
		int l=1,lg=0;
		while(l<=d){
			l<<=1;
			++lg;
		}
		if(l==last) return;
		lim=l,L=lg;
		r.assign(lim,0);
		for(int i=0;i<lim;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(L-1));
		}
	}
	void poly_mul(Poly& a,Poly& b){ // a=a*b, b is changed
		const int n=a.size()-1;
		const int m=b.size()-1;
		if(min(n,m)<=64){
			Poly c(n+m+1);
			for(int i=0;i<=n;++i){
				for(int j=0;j<=m;++j){
					LL x=a[i]*b[j]%mo;
					ADD(c[i+j],x);
				}
			}
			swap(a,c);
			return;
		}
		init(n+m);
		a.resize(lim); NTT(a,1);
		b.resize(lim); NTT(b,1);
		for(int i=0;i<lim;i++){
			a[i]=(a[i]*b[i])%mo;
		}
		NTT(a,-1);
		a.resize(n+m+1);
	}
}
using NTT::init_mod;
using NTT::poly_mul;

// a[(i*j)%P]+=a[i]*a[j]%mod;
int P,g; // g is pr of P
Poly conv(const Poly& a,const Poly& b){
	vector<LL>aa(P-1),bb(P-1);
	for(int i=0,x=1;i<P-1;++i){
		aa[i]=a[x];
		bb[i]=b[x];
		x=x*g%P;
	}
	poly_mul(aa,bb);
	for(int i=P-1;i<aa.size();++i){
		int j=i%(P-1);
		aa[j]=(aa[j]+aa[i])%mod;
	}
	vector<LL>d(P);
	for(int i=0,x=1;i<P-1;++i){
		d[x]=aa[i];
		x=x*g%P;
	}
	return d;
}

init_prime();
init_mod(TODO_NTT_MOD);
g=prim_root(P); // this is for conv(a,b)
