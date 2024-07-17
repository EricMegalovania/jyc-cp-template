struct Mod{ //Barrett Reduction
	LL mod,base;
	Mod(){}
	Mod(const LL& M){
		mod=M,base=(__int128_t(1)<<64)/M;
	}
	friend LL operator +(const LL& x,const Mod& M){
		return x<0?x+M.mod:x;
	}
	friend LL operator %(LL x,const Mod& M){
		return x-((__int128_t(x)*M.base)>>64)*M.mod;
	}
	friend LL operator %=(const LL& x,const Mod& M){
		return x%M;
	}
}mod;

mod=read(); //初始化，实际为 mod=Mod((LL)read())
