using big=__int128_t;
LL sqrt_approx(LL x){
	LL approx=sqrt(double(x));
	return (approx+x/approx)>>1;
}
LL sqrt_ll(LL x){
	LL approx=sqrt(double(x));
	LL apt=(approx+x/approx)>>1;
	approx=apt*apt;
	if(approx>x)return apt-1;
	if(x-approx>=2*apt-1)return apt+1;
	return apt;
}
big sqrt_big(big r){
	if(!(r>>64))return sqrt_ll(LL(r));
	int cnt=(((64-__builtin_clzll(LL(r>>64)))+1)|1)^1;
	big approx=big(sqrt_approx(LL(r>>cnt)))<<(cnt/2);
	approx=(approx+r/approx)>>1;
	big apt=big(LL(approx))*big(LL(approx));
//  if(r-apt>=2*approx-1)return approx+1;
	return approx-((r-apt)>>127);
}
