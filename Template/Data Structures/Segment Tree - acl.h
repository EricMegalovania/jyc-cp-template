#define ls (p<<1)
#define rs (p<<1|1)
#define PP int mid=(q[p].l+q[p].r)>>1
template<class S,auto op,auto e>
struct _SGT{ // acl-like segtree
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
	template<class G>
	int _minl(int r,G g,S& s,int p=1){
		if(q[p].r==r){
			S ns=op(q[p].s,s);
			if(g(ns)) return s=ns,q[p].l;
		}
		if(q[p].l==q[p].r) return q[p].l+1;
		PP;
		if(r<=mid) return _minl(r,g,s,ls);
		else{
			int res=_minl(r,g,s,rs);
			if(res>mid+1) return res;
			else return _minl(mid,g,s,ls);
		}
	}
	template<class G>
	int _maxr(int l,G g,S& s,int p=1){
		if(q[p].l==l){
			S ns=op(s,q[p].s);
			if(g(ns)) return s=ns,q[p].r;
		}
		if(q[p].l==q[p].r) return q[p].r-1;
		PP;
		if(l>mid) return _maxr(l,g,s,rs);
		else{
			int res=_maxr(l,g,s,ls);
			if(res<mid) return res;
			else return _maxr(mid+1,g,s,rs);
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
	template<auto g>
	int min_left(int r){ return min_left<decltype(g)>(r,g); }
	template<class G>
	int min_left(int r,G g){
		assert(q[1].l<=r && r<=q[1].r);
		S s=e(); return max(q[1].l,_minl(r,g,s));
	}
	template<auto g>
	int max_right(int l){ return max_right<decltype(g)>(l,g); }
	template<class G>
	int max_right(int l,G g){
		assert(q[1].l<=l && l<=q[1].r);
		S s=e(); return min(q[1].r,_maxr(l,g,s));
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
using def::S,def::SGT;
