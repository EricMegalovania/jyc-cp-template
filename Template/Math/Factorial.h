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
	LL fc[N]={1},fc_inv[N]={1};
	void init(){
		for(int i=1;i<N;i++){
			fc[i]=fc[i-1]*i%mod;
			fc_inv[i]=fc_inv[i-1]*ksm(i,mod-2)%mod;
		}
	}
	LL F(const int& x){
		return fc[x];
	}
	LL P(const int& x,const int& y){
		return fc[x]*fc_inv[x-y]%mod;
	}
	LL C(const int& x,const int& y){
		return fc[x]*fc_inv[y]%mod*fc_inv[x-y]%mod;
	}
}

Fac::init(); //初始化
