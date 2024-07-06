//返回最大的整数p, p的b次方<=a
//即, 返回 a^(1/b) 的下取整值 (自带的 pow 和 sqrt 精度堪忧)
LL pow_inv(LL a,LL b){
	LL offset=pow(a,(long double)1.0/b);
	static auto check=[](LL a,LL b,LL lim)->bool{
		LL res=1; bool flag=a>lim;
		while(b){
			if(b&1){
				if(flag || !(res<=lim/a)) return 0;
				res*=a;
			}
			if(a<=lim/a) a*=a;
			else flag=1;
			b>>=1;
		}
		return 1;
	};
	for(LL p=offset+5;p>=offset-5;p--){
		if(check(p,b,a)) return p;
	}
	exit(-1);
}
