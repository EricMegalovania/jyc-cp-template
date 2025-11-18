#define ls (p<<1)
#define rs (p<<1|1)
#define PP int mid=(q[p].l+q[p].r)>>1
template<class S,auto op,auto e>
struct _SGT{ // acl-like lazy_segtree
private:
	struct Node{ int l,r; S s; };
	vector<Node>q;
	void pull(int p){ q[p].s=op(q[ls].s,q[rs].s); }
	void build(const vector<S>& a,int l,int r,int p=1){
		q[p].l=l,q[p].r=r;
		if(l==r) return (void)(q[p].s=a[l]);
		int mid=(l+r)>>1;
		build(a,l,mid,ls);
		build(a,mid+1,r,rs);
		pull(p);
	}
	template<class F>
	int _minl(int r,F f,S& s,int p){
		if(q[p].r==r){
			S ns=op(q[p].s,s);
			if(f(ns)) return s=ns,q[p].l;
		}
		if(q[p].l==q[p].r) return q[p].l+1;
		PP;
		if(r<=mid) return _minl(r,f,s,ls);
		else{
			int res=_minl(r,f,s,rs);
			if(res>mid+1) return res;
			else return _minl(mid,f,s,ls);
		}
	}
	template<class F>
	int _maxr(int l,F f,S& s,int p){
		if(q[p].l==l){
			S ns=op(s,q[p].s);
			if(f(ns)) return s=ns,q[p].r;
		}
		if(q[p].l==q[p].r) return q[p].r-1;
		PP;
		if(l>mid) return _maxr(l,f,s,rs);
		else{
			int res=_maxr(l,f,s,ls);
			if(res<mid) return res;
			else return _maxr(mid+1,f,s,rs);
		}
	}
public:
	_SGT(int n){ init(n); }
	_SGT(const vector<S>& a,int n){ init(a,n); }
	void init(int n){ init(vector<S>(n+1,e()),n); }
	void init(const vector<S>& a,int n){ q.resize(n*4+10); build(a,1,n); }
	S query(int l,int r,int p=1){
		if(q[p].l==l && q[p].r==r) return q[p].s;
		PP;
		if(r<=mid) return query(l,r,ls);
		else if(l>mid) return query(l,r,rs);
		else return op(query(l,mid,ls),query(mid+1,r,rs));
	}
	void set(int x,S s,int p=1){
		if(q[p].l==q[p].r) return (void)(q[p].s=s);
		PP;
		if(x<=mid) set(x,s,ls);
		else set(x,s,rs);
		pull(p);
	}
	S at(int x,int p=1){
		if(q[p].l==q[p].r) return q[p].s;
		PP;
		if(x<=mid) return at(x,ls);
		else return at(x,rs);
	}
	template<auto f>
	int min_left(int r){ return min_left<decltype(f)>(r,f); }
	template<class F>
	int min_left(int r,F f){
		if(r<1 || r>q[1].r) return -1;
		S s=e(); return max(1,_minl(r,f,s,1));
	}
	template<auto f>
	int max_right(int l){ return max_right<decltype(f)>(l,f); }
	template<class F>
	int max_right(int l,F f){
		if(l<1 || l>q[1].r) return -1;
		S s=e(); return min(q[1].r,_maxr(l,f,s,1));
	}
};
#undef PP
#undef ls
#undef rs

namespace def{ // example: single set, range sum
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
	using SGT=_SGT<S,op,e>;
};
using def::SGT;
