namespace FMF{ //find-max-factor
	using big=__int128_t;
	LL gcd(LL a,LL b){
		return b?gcd(b,a%b):a;
	}
	LL ksm(LL a,LL b,LL p){
		a%=p; LL res=1;
		while(b){
			if(b&1) res=(big)res*a%p;
			a=(big)a*a%p;
			b>>=1;
		}
		return res;
	}
	bool Miller_Rabin(LL p){ //判断素数
		if(p<2) return 0;
		if(p==2 || p==3 || p==5 || p==7 || p==43) return 1;
		LL d=p-1,r=0;
		while(!(d&1)) ++r,d>>=1; //将d处理为奇数
		for(LL k=0;k<10;k++) {
			LL a=rng()%(p-2)+2;
			LL x=ksm(a,d,p);
			if(x==1 || x==p-1) continue;
			for(int i=0;i<r-1;i++){
				x=(big)x*x%p;
				if(x==p-1) break;
			}
			if(x!=p-1) return 0;
		}
		return 1;
	}
	LL Pollard_Rho(LL x){
		LL s=0,t=0,c=rng()%(x-1)+1;
		int step=0,goal=1;
		LL val=1;
		for(goal=1;;goal<<=1,s=t,val=1){ //倍增优化
			for(step=1;step<=goal;step++){
				t=((big)t*t+c)%x;
				val=(big)val*abs(t-s)%x;
				if((step%127)==0){
					LL d=gcd(val,x);
					if(d>1) return d;
				}
			}
			LL d=gcd(val,x);
			if(d>1) return d;
		}
	}
	LL max_factor;
	void fac(LL x){
		if(x<=max_factor || x<2) return;
		if(Miller_Rabin(x)){ //如果x为质数
			max_factor=max(max_factor,x); //更新答案
			return;
		}
		LL p=x;
		while(p>=x) p=Pollard_Rho(x);  //使用该算法
		while((x%p)==0) x/=p;
		fac(x),fac(p); //继续向下分解x和p
	}
}

n=readLL(); //n是待分解的大数
while(n>=N){ //N是用筛法筛的质数的范围
	FMF::max_factor=0;
	FMF::fac(n);
	LL d=FMF::max_factor;
	while(n%d==0) n/=d;
}
