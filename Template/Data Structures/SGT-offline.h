struct DSU{
	vector<int>fa,siz;
	stack<ai3>stk;
	DSU(){}
	DSU(int n){init(n);}
	void init(int n){
		fa.resize(n);
		iota(all(fa),0);
		siz.assign(n,0);
	}
	int get(int x){
		while(x!=fa[x]) x=fa[x];
		return x;
	}
	void merge(int u,int v){
		u=get(u),v=get(v);
		if(u==v) return;
		if(siz[u]<siz[v]) swap(u,v);
		//u is v's fa
		stk.push({v,u,siz[u]});
		siz[u]+=siz[u]==siz[v];
		fa[v]=u;
	}
	void undo(){
		auto [v,u,sizu]=stk.top();
		stk.pop();
		fa[v]=v;
		siz[u]=sizu;
	}
};

vector<int>ans; //
#define ls (id<<1)
#define rs (id<<1|1)
class SGT{
private:
	struct Node{
		int l,r;
		//
	};
	vector<Node>q;
	void build(int l,int r,int id=1){
		q[id].l=l,q[id].r=r;
		if(l==r) return;
		int mid=l+r>>1;
		build(l,mid,ls);
		build(mid+1,r,rs);
	}
public:
	SGT(int n){
		init(n);
	}
	void init(int n){
		q.resize(n*5);
		build(1,n);
	}
	void modify(int l,int r,const ai2& x,int id=1){
		if(q[id].l==l && q[id].r==r){
			//
			return;
		}
		int mid=q[id].l+q[id].r>>1;
		if(r<=mid) modify(l,r,x,ls);
		else if(l>mid) modify(l,r,x,rs);
		else modify(l,mid,x,ls),modify(mid+1,r,x,rs);
	}
	void rua(int id=1){
		//
		if(q[id].l==q[id].r){
			//
		}
		else{
			rua(ls);
			rua(rs);
		}
		POP:
		//
	}
};
#undef ls
#undef rs
