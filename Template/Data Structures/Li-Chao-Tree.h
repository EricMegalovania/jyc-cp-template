using LD=long double;
using PDI=pair<LD,int>;
constexpr LD eps=1e-8;
constexpr int UPD=1; // use -1 to keep small
LD fupd(const LD x,const LD y){
	if constexpr (UPD==1) return fmax(x,y);
	else return fmin(x,y);
}

inline int sign(const LD x){
	if(fabs(x)<eps) return 0;
	return x>(LD)(0)?1:-1;
}
inline int dcmp(const LD x,const LD y){
	return sign(x-y);
}

#define L q[id].l
#define R q[id].r
#define LS q[id].ls
#define RS q[id].rs
class LCT{ // li-chao-tree, UPD=1 to keep big
private:
	struct Line{
		LD k,b;
	};
	vector<Line>a;
	inline LD calc(const int id,const LD x){
		return a[id].k*x+a[id].b;
	}
	struct Node{
		int l,r,ls,rs,best_id;
	};
	vector<Node>q;
	void New(int& fa,int l,int r){
		if(fa) return;
		fa=int(q.size());
		q.push_back(Node{l,r,0,0,-1});
	}
	void update(int id,int line_id){
		// 不能用指针或者引用, 否则 vector 重分配会导致 UB
#define nw_id q[id].best_id
        const int mid=(L+R)>>1;
		if(nw_id==-1){
			nw_id=line_id;
			return;
		}
		int cmp_mid=dcmp(calc(line_id,mid),calc(nw_id,mid));
		// keep big or (same but id small)
		if(cmp_mid==UPD || (!cmp_mid && line_id<nw_id)){
			swap(nw_id,line_id);
		}
		int cmp_l=dcmp(calc(line_id,L),calc(nw_id,L));
		if(cmp_l==UPD || (!cmp_l && line_id<nw_id)){
			New(LS,L,mid);
			update(LS,line_id);
		}
		int cmp_r=dcmp(calc(line_id,R),calc(nw_id,R));
		if(cmp_r==UPD || (!cmp_r &&  line_id<nw_id)){
			New(RS,mid+1,R);
			update(RS,line_id);
		}
#undef nw_id
	}
	void modify(int l,int r,int line_id,int id=1){
		if(L==l && R==r){
			update(id,line_id);
			return;
		}
		int mid=(L+R)>>1;
		New(LS,L,mid),New(RS,mid+1,R);
		if(r<=mid) modify(l,r,line_id,LS);
		else if(l>mid) modify(l,r,line_id,RS);
		else{
			modify(l,mid,line_id,LS);
			modify(mid+1,r,line_id,RS);
		}
	}
public:
	LCT(){}
	LCT(int _L,int _R){
		init(_L,_R);
	}
	void init(int _L,int _R){
		q.clear(); q.push_back(Node{});
        a.clear(); a.push_back(Line{});
		q.push_back(Node{_L,_R,0,0,-1});
	}
	void insert(int x0,int y0,int x1,int y1){
		int id=int(a.size());
		if(x0==x1){
			a.push_back(Line{0,fupd(LD(y0),LD(y1))});
		}
		else{
			LD k=LD(y1-y0)/LD(x1-x0);
			a.push_back(Line{k,LD(y1)-k*x1});
		}
		modify(x0,x1,id);
	}
	PDI query(int pos,int id=1){
		const int& u=q[id].best_id;
		PDI res;
		if(u==-1) res=PDI{0,0};
		else res=PDI{calc(u,pos),u};
		if(L==R) return res;
		int mid=(L+R)>>1;
		PDI ret;
		if(pos<=mid) ret=query(pos,LS);
		else ret=query(pos,RS);
		int cmp=dcmp(ret.first,res.first);
		if(cmp==UPD || (!cmp && ret.second<res.second)){
			swap(res,ret);
		}
		return res;
	}
};
#undef L
#undef R
#undef LS
#undef RS
