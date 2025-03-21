namespace ST_C{ //Sparse Table Constant
	int Logn[N];
	void init(){
		Logn[1]=1,Logn[2]=2;
		for (int i=3;i<N;i++) {
			Logn[i]=Logn[i/2]+1;
		}
	}
}
#define ls (id<<1)
#define rs (id<<1|1)
#define ID(x) (x+nn-1)
class CatSGT{ //Cat-SGT
private:
	static int nn;
	struct Node{
		int l,r;
		//pre:(mid,r] suf:[l,mid]
		vector<DP>pre,suf; //modify type
	};
	vector<Node>q;
	void build(const auto& a,int l,int r,int n,const auto& void_val,int id=1){
		q[id].l=l,q[id].r=r;
		auto& pre=q[id].pre;
		auto& suf=q[id].suf;
#define val(x) ((x)<=n?a[x]:void_val)
		if(l==r){
			pre={};
			suf={val(l)}; //modify
			return;
		}
		int mid=l+r>>1;
		build(a,l,mid,n,void_val,ls);
		build(a,mid+1,r,n,void_val,rs);
		suf.resize(mid-l+1);
		suf[0]=val(mid); //modify
		for(int i=1;i<mid-l+1;i++){ //modify
			suf[i]=suf[i-1],val(mid-i);
		}
		pre.resize(r-mid);
		pre[0]=val(mid+1); //modify
		for(int i=1;i<r-mid;i++){ //modify
			pre[i]=pre[i-1],val(mid+i+1);
		}
#undef val
	}
public:
	CatSGT(const auto& a,int n){
		init(a,n);
	}
	void init(const auto& a,int n){
		CatSGT::nn=1<<ST_C::Logn[n];
		if(nn/2>=n) nn/=2;
		q.resize(nn*2+1);
		const LL& void_val=0; //modify
		build(a,1,nn,n,void_val);
	}
	auto query(int l,int r){
		const auto& u=q[ID(l)>>ST_C::Logn[ID(l)^ID(r)]];
		const int& mid=u.l+u.r>>1;
		if(mid==r) return u.suf[mid-l]; //modify
		return u.pre[r-mid-1],u.suf[mid-l]; //modify
	}
};
int CatSGT::nn;
#undef ls
#undef rs
#undef ID

ST_C::init();
