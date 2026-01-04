constexpr int N=TODO;
bitset<N>notP,haspr; int phi[N],mn_p[N];
vector<int>prime;
void init_prime(const int& n=N){  // init [1,n-1]
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
	for(int i=1;i<(int)prime.size();++i){
		int p=prime[i];
		for(LL j=p;j<N;j*=p) haspr[j]=1;
		for(LL j=2*p;j<N;j*=p) haspr[j]=1;
	}
}

constexpr LL qpow(LL a,LL b,LL p){
	a%=p; LL r=1;
	while(b){
		if(b&1) r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}

bitset<N>cop;
template<bool ALLPR=false>
auto prim_root(int n){  // primitive root
#define RET(x) { if constexpr(!ALLPR) return x; else return vector<int>{x}; }
	if(!haspr[n]) RET(0);
	if(n==2 || n==4) RET(n-1);
#undef RET
	int tmp=phi[n];
	vector<int>d;
	while(1){
		const int p=mn_p[tmp];
		if(p==1) break;
		d.emplace_back(p);
		do{ tmp/=p; }while(tmp%p==0);
	}
	int mnpr=1;
	for(;;++mnpr){
		for(;__gcd(mnpr,n)!=1;++mnpr);
		int j=0;
		for(;j<(int)d.size() && qpow(mnpr,phi[n]/d[j],n)!=1;++j);
		if(j>=(int)d.size()) break;
	}
	if constexpr (!ALLPR) return mnpr;
	else{
		tmp=mnpr;
		for(auto p:d){
			for(int j=p;j<phi[n];j+=p) cop[j]=1;
		}
		vector<int>pr; // size is phi(phi(n))
		for(int i=1;i<phi[n];++i,tmp=tmp*mnpr%n){
			if(!cop[i]) pr.emplace_back(tmp);
			else cop[i]=0;
		}
		sort(all(pr));
		return pr;
	}
}

init_prime();
prim_root<TODO>(); // 0: mnpr, 1: allpr