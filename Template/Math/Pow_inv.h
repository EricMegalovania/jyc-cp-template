//返回最大的整数x, x的b次方<=a
//即, 返回 a^(1/b) 的下取整值 (自带的 pow 和 sqrt 精度堪忧)
LL pow_inv(LL a,LL b){
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
	LL x=pow(a,(long double)1.0/b);
	while(!check(x,b,a)) x--;
	while(check(x+1,b,a)) x++;
	return x;
}
