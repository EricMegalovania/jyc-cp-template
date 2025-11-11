#define ls (p<<1)
#define rs (p<<1|1)
template<class S,auto op,auto e,class F,auto mp,auto comp,auto id>
struct _SGT{ // acl-like lazy_segtree
private:
	struct Node{ int l,r; S s; F f; };
	vector<Node>q;
	void update(int p,const F& f){
		Node& u=q[p]; u.s=mp(f,u.s);
		if(u.l!=u.r){
			u.f=comp(f,u.f);
//			if(u.s.fail) push(p),pull(p);
		}
//		else assert(!u.s.fail);
	}
	void push(int p){
		if(q[p].l==q[p].r) return;
		update(ls,q[p].f);
		update(rs,q[p].f);
		q[p].f=id();
	}
	void pull(int p){ q[p].s=op(q[ls].s,q[rs].s); }
	void build(const vector<S>& a,int l,int r,int p=1){
		q[p].l=l,q[p].r=r,q[p].f=id();
		if(l==r) return (void)(q[p].s=a[l]);
		int mid=(l+r)>>1;
		build(a,l,mid,ls);
		build(a,mid+1,r,rs);
		pull(p);
	}
public:
	_SGT(int n){ init(n); }
	_SGT(const vector<S>& a,int n){ init(a,n); }
	void init(int n){ init(vector<S>(n+1,e()),n); }
	void init(const vector<S>& a,int n){ q.resize(n*4+10); build(a,1,n); }
	void modify(int l,int r,const F& f,int p=1){
		if(q[p].l==l && q[p].r==r) return (void)(update(p,f));
		push(p);
		int mid=(q[p].l+q[p].r)>>1;
		if(r<=mid) modify(l,r,f,ls);
		else if(l>mid) modify(l,r,f,rs);
		else modify(l,mid,f,ls),modify(mid+1,r,f,rs);
		pull(p);
	}
	S query(int l,int r,int p=1){
		if(q[p].l==l && q[p].r==r) return q[p].s;
		push(p);
		int mid=(q[p].l+q[p].r)>>1;
		if(r<=mid) return query(l,r,ls);
		else if(l>mid) return query(l,r,rs);
		else return op(query(l,mid,ls),query(mid+1,r,rs));
	}
	void set(int x,S s,int p=1){
		if(q[p].l==q[p].r) return (void)(q[p].s=s);
		push(p);
		int mid=(q[p].l+q[p].r)>>1;
		if(x<=mid) set(x,s,ls);
		else set(x,s,rs);
		pull(p);
	}
	S at(int x,int p=1){
		if(q[p].l==q[p].r) return q[p].s;
		push(p);
		int mid=(q[p].l+q[p].r)>>1;
		if(x<=mid) return at(x,ls);
		else return at(x,rs);
	}
};
#undef ls
#undef rs

namespace def{ // example: range add, range sum
	struct S{
		LL s; // sum
		int l; // len
	};
	S op(S a,S b){ // new s = a op b
		return S{a.s+b.s,a.l+b.l};
	}
	S e(){ // x op e() = e() op x = x
		return S{0,0};
	}
	using F=LL;
	S mapping(F f,S x){ // x -> f(x)
		return S{x.s+f*x.l,x.l};
	}
	F composition(F f,F g){ // f(g(x))
		return f+g;
	}
	F id(){ // id(x) = x
		return 0;
	}
	using SGT=_SGT<S,op,e,F,mapping,composition,id>;
};
using def::SGT;
