const int HL=2;//hash layer
using ALH=array<LL,HL>;
namespace HC{//Hash Const
	const int P[4]={13331,233,131,19260817};
	const int MOD[4]={(int)(1e9+7),998244353,1004535809,754974721};
	LL ksm[N][4];
	void init(){
		for(int j=0;j<HL;j++){
			ksm[0][j]=1;
			for(int i=1;i<N;i++){
				ksm[i][j]=(ksm[i-1][j]*P[j])%MOD[j];
			}
		}
	}
}
class Hash{
private:
	vector<ALH>h;
	bool sign;//0:normal 1:reverse
public:
	Hash(){}
	Hash(char *s,int n,bool sign_=0){
		init(s,n,sign_);
	}
	void init(char *s,int n,bool sign_=0){//s stores at pos [1,n], and just give para s (NOT s+1)
		h.resize(n+2);
		sign=sign_;
		if(!sign){
			for(int j=0;j<HL;j++){
				h[0][j]=0;
				for(int i=1;i<=n;i++){
					h[i][j]=(h[i-1][j]*HC::P[j]+s[i]-'a'+1)%HC::MOD[j];
				}
			}
		}
		else{
			for(int j=0;j<HL;j++){
				h[n+1][j]=0;
				for(int i=n;i>0;i--){
					h[i][j]=(h[i+1][j]*HC::P[j]+s[i]-'a'+1)%HC::MOD[j];
				}
			}
		}
	}
	ALH calc(const int& l,const int& r){
		static ALH ret;
		if(!sign){
			for(int j=0;j<HL;j++){
				ret[j]=h[r][j]-h[l-1][j]*HC::ksm[r-l+1][j];
			}
		}
		else{
			for(int j=0;j<HL;j++){
				ret[j]=h[l][j]-h[r+1][j]*HC::ksm[r-l+1][j];
			}
		}
		for(int j=0;j<HL;j++){
			ret[j]=(ret[j]%HC::MOD[j]+HC::MOD[j])%HC::MOD[j];
		}
		return ret;
	}
	static bool check(const ALH& a,const ALH& b){
		for(int i=0;i<HL;i++){
			if(a[i]!=b[i]) return 0;
		}
		return 1;
	}
};
ALH operator <<(const ALH& A,const int& len){
	static ALH ret;
	for(int i=0;i<HL;i++){
		ret[i]=(A[i]*HC::ksm[len][i])%HC::MOD[i];
	}
	return ret;
}
ALH operator +(const ALH& A,const ALH& B){
	static ALH ret;
	for(int i=0;i<HL;i++){
		ret[i]=(A[i]+B[i])%HC::MOD[i];
	}
	return ret;
}
ALH operator -(const ALH& A,const ALH& B){
	static ALH ret;
	for(int i=0;i<HL;i++){
		ret[i]=((A[i]-B[i])%HC::MOD[i]+HC::MOD[i])%HC::MOD[i];
	}
	return ret;
}
ALH operator *(const ALH& A,const ALH& B){
	static ALH ret;
	for(int i=0;i<HL;i++){
		ret[i]=A[i]*B[i]%HC::MOD[i];
	}
	return ret;
}

HC::init(); //初始化
