namespace Fac{ // factorial
	constexpr int N=TODO;
	Z fc[N],fc_inv[N];
	void init(){
		fc[0]=fc_inv[0]=raw(1);
		for(int i=1;i<N;i++){
			fc[i]=fc[i-1]*raw(i);
		}
		fc_inv[N-1]=fc[N-1].inv();
		for(int i=N-2;i>0;i--){
			fc_inv[i]=fc_inv[i+1]*raw(i+1);
		}
	}
	Z P(const int x,const int y){
		return fc[x]*fc_inv[x-y];
	}
	Z C(const int x,const int y){
		if(x==y) return raw(1);
		if(x<0 || y<0 || x-y<0) return raw(0);
		return fc[x]*fc_inv[y]*fc_inv[x-y];
	}
}

// check mod !!!!
Fac::init();