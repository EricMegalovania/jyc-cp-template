using LD=long double;
using PDI=pair<LD,int>;
const LD eps=1e-8;

inline int sign(const LD& x){
	if(fabs(x)<eps) return 0;
	return x>(LD)(0.0)?1:-1;
}
inline int dcmp(const LD& x,const LD& y){
	return sign(x-y);
}

class LCT{ //li-chao-tree, keep big
private:
	struct Line{
		LD k,b;
	};
	vector<Line>a;
	inline LD calc(const int& id,const LD& x){
		return a[id].k*x+a[id].b;
	}
	struct Node{
		int l,r,ls,rs,best_id;
	};
	vector<Node>q;
	void New(int& fa,int l,int r){
		if(fa) return;
		fa=q.size();
		q.push_back(Node{l,r,0,0,-1});
	}
	void update(int id,int line_id){
		const int& l=q[id].l,r=q[id].r;
		int &nw_id=q[id].best_id,mid=l+r>>1;
		if(nw_id==-1){
			nw_id=line_id;
			return;
		}
		int cmp_mid=dcmp(calc(line_id,mid),calc(nw_id,mid));
		//keep big or (same but id small)
		if(cmp_mid==1 || (!cmp_mid && line_id<nw_id)){
			swap(nw_id,line_id);
		}
		int cmp_l=dcmp(calc(line_id,l),calc(nw_id,l));
		if(cmp_l==1 || (!cmp_l && line_id<nw_id)){
			New(q[id].ls,q[id].l,mid);
			update(q[id].ls,line_id);
		}
		int cmp_r=dcmp(calc(line_id,r),calc(nw_id,r));
		if(cmp_r==1 || (!cmp_r &&  line_id<nw_id)){
			New(q[id].rs,mid+1,q[id].r);
			update(q[id].rs,line_id);
		}
	}
	void modify(int l,int r,int line_id,int id=1){
		if(q[id].l==l && q[id].r==r){
			update(id,line_id);
			return;
		}
		int mid=q[id].l+q[id].r>>1;
		New(q[id].ls,q[id].l,mid),New(q[id].rs,mid+1,q[id].r);
		if(r<=mid) modify(l,r,line_id,q[id].ls);
		else if(l>mid) modify(l,r,line_id,q[id].rs);
		else{
			modify(l,mid,line_id,q[id].ls);
			modify(mid+1,r,line_id,q[id].rs);
		}
	}
public:
	LCT(){}
	LCT(int L,int R){
		init(L,R);
	}
	void init(int L,int R){
		vector<Node>{Node{}}.swap(q);
		vector<Line>{Line{}}.swap(a);
		q.push_back(Node{L,R,0,0,-1});
	}
	void insert(LD x0,LD y0,LD x1,LD y1){
		int id=a.size();
		if(x0==x1){
			a.push_back(Line{0,max(y0,y1)});
		}
		else{
			LD k=(LD)(1.0)*(y1-y0)/(x1-x0);
			a.push_back(Line{k,y1-k*x1});
		}
		modify(x0,x1,id);
	}
	PDI query(int pos,int id=1){
		const int& u=q[id].best_id;
		PDI res;
		if(u==-1) res=PDI{0,0};
		else res=PDI{calc(u,pos),u};
		if(q[id].l==q[id].r) return res;
		int mid=q[id].l+q[id].r>>1;
		PDI ret;
		if(pos<=mid) ret=query(pos,q[id].ls);
		else ret=query(pos,q[id].rs);
		int cmp=dcmp(ret.first,res.first);
		if(cmp==1 || (!cmp && ret.second<res.second)){
			swap(res,ret);
		}
		return res;
	}
};
