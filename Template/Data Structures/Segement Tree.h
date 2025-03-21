#define ls (id<<1)
#define rs (id<<1|1)
class SGT{//以线段树维护区间最大值为例，支持区间修改
private:
	struct Node{
		int l,r;
		int mx; bool tag;
		friend Node operator +(const Node& A,const Node& B){
			Node ret;
			ret.l=A.l,ret.r=B.r;
			
			//update the main content
			ret.mx=max(A.mx,B.mx);
			ret.tag=0;
			
			return ret;
		}
	};
	vector<Node>q;
	void spread(int id){
		if(q[id].l==q[id].r) return;
		//spread the lazy tag
		if(q[id].tag){
			q[ls].mx=q[id].mx;
			q[rs].mx=q[id].mx;
			q[ls].tag=1;
			q[rs].tag=1;
			q[id].tag=0;
		}
	}
	void build(const auto& a,int l,int r,int id=1){
		if(l==r){
			q[id].l=l,q[id].r=r;
			
			//init value
			q[id].mx=a[l],q[id].tag=0;
			
			return;
		}
		int mid=l+r>>1;
		build(a,l,mid,ls);
		build(a,mid+1,r,rs);
		q[id]=q[ls]+q[rs];
	}
public:
	SGT(const auto& a,int n){
		init(a,n);
	}
	void init(const auto& a,int n){
		q.resize(n*5);
		build(a,1,n);
	}
	void modify(int l,int r,int val,int id=1){
		if(q[id].l==l && q[id].r==r){
			//modify the value
			q[id].mx=max(q[id].mx,val),q[id].tag=1;
			return;
		}
		spread(id);
		int mid=q[id].l+q[id].r>>1;
		if(r<=mid) modify(l,r,val,ls);
		else if(l>mid) modify(l,r,val,rs);
		else modify(l,mid,val,ls),modify(mid+1,r,val,rs);
		q[id]=q[ls]+q[rs];
	}
	int query(int l,int r,int id=1){
		if(q[id].l==l && q[id].r==r) return q[id].mx;
		spread(id);
		int mid=q[id].l+q[id].r>>1;
		if(r<=mid) return query(l,r,ls);
		else if(l>mid) return query(l,r,rs);
		return max(query(l,mid,ls),query(mid+1,r,rs));
	}
	int get(int pos,int id=1){
		if(q[id].l==q[id].r) return q[id].mx;
		spread(id);
		int mid=q[id].l+q[id].r>>1;
		if(pos<=mid) return get(pos,ls);
		return get(pos,rs);
	}
};
#undef ls
#undef rs
