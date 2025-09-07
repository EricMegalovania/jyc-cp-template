const int mod=1e9+7;
LL ksm(LL a,LL b){
	a%=mod; LL ret=1;
	while(b){
		if(b&1) ret=ret*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ret;
}

namespace Fac{//factorial
	LL fc[N],fc_inv[N];
	void init(){
		fc[0]=fc_inv[0]=1;
		for(int i=1;i<N;i++){
			fc[i]=fc[i-1]*i%mod;
		}
		fc_inv[N-1]=ksm(fc[N-1],mod-2);
		for(int i=N-2;i>0;i--){
			fc_inv[i]=fc_inv[i+1]*(i+1)%mod;
		}
	}
	LL F(const int& x){
		return fc[x];
	}
	LL P(const int& x,const int& y){
		return fc[x]*fc_inv[x-y]%mod;
	}
	LL C(const int& x,const int& y){
		if(x==y) return 1;
		if(x<0 || y<0 || x-y<0) return 0;
		return fc[x]*fc_inv[y]%mod*fc_inv[x-y]%mod;
	}
}

// check mod !!!!
Fac::init(); //初始化
