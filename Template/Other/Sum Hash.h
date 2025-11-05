using ALH=array<LL,2>; // array-LL-Hash
namespace HC{ // Hash Const
	const int MOD[4]={(int)(1e9+7),998244353};
	LL inv(const LL& A,const int& _){
		LL a=A%MOD[_]; LL b=MOD[_]-2,res=1;
		while(b){
			if(b&1) res=res*a%MOD[_];
			a=a*a%MOD[_];
			b>>=1;
		}
		return res;
	}
}
ALH operator +(const ALH& A,const ALH& B){
	static ALH res;
	for(int i=0;i<2;i++){
		res[i]=(A[i]+B[i])%HC::MOD[i];
	}
	return res;
}
ALH operator -(const ALH& A,const ALH& B){
	static ALH res;
	for(int i=0;i<2;i++){
		res[i]=((A[i]-B[i])%HC::MOD[i]+HC::MOD[i])%HC::MOD[i];
	}
	return res;
}
ALH operator *(const ALH& A,const ALH& B){
	static ALH res;
	for(int i=0;i<2;i++){
		res[i]=A[i]*B[i]%HC::MOD[i];
	}
	return res;
}
ALH operator /(const ALH& A,const ALH& B){
	static ALH res;
	for(int i=0;i<2;i++){
		res[i]=A[i]*HC::inv(B[i],i)%HC::MOD[i];
	}
	return res;
}
