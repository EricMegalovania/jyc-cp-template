#define ls (q[p].lson)
#define rs (q[p].rson)
#define PP T mid=(q[p].l+q[p].r)>>1; ensure_child(p,mid)
template<class T,class S,auto op,auto e>
struct _SGT{ // acl-like dynamic segtree
private:
	static_assert(std::is_integral_v<T>);
	struct Node{
		T l,r; S s;
		int lson,rson;
		Node(T _l,T _r):l(_l),r(_r),s(e()),lson(0),rson(0){}
	};
	vector<Node>q;
	int _new(T l,T r){
		int id=(int)q.size();
		q.emplace_back(l,r);
		return id;
	}
	void ensure_child(int p,T mid){
		if(q[p].l==q[p].r) return;
		if(!ls) ls=_new(q[p].l,mid);
		if(!rs) rs=_new(mid+1,q[p].r);
	}
	void pull(int p){ q[p].s=op(q[ls].s,q[rs].s); }
	template<class F>
	T _minl(T r,F f,S& s,int p=1){
		if(q[p].r==r){
			S ns=op(q[p].s,s);
			if(f(ns)) return s=ns,q[p].l;
		}
		if(q[p].l==q[p].r) return q[p].l+1;
		PP;
		if(r<=mid) return _minl(r,f,s,ls);
		else{
			T res=_minl(r,f,s,rs);
			if(res>mid+1) return res;
			else return _minl(mid,f,s,ls);
		}
	}
	template<class F>
	T _maxr(T l,F f,S& s,int p=1){
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
	_SGT(T L,T R){ init(L,R); }
	void init(T L,T R){ q.clear(); _new(0,0); _new(L,R); }
	S query(T l,T r,int p=1){
		if(q[p].l==l && q[p].r==r) return q[p].s;
		PP;
		if(r<=mid) return query(l,r,ls);
		else if(l>mid) return query(l,r,rs);
		else return op(query(l,mid,ls),query(mid+1,r,rs));
	}
	void set(T x,S s,int p=1){
		if(q[p].l==q[p].r) return (void)(q[p].s=s);
		PP;
		if(x<=mid) set(x,s,ls);
		else set(x,s,rs);
		pull(p);
	}
	S at(T x,int p=1){
		if(q[p].l==q[p].r) return q[p].s;
		PP;
		if(x<=mid) return at(x,ls);
		else return at(x,rs);
	}
	template<auto f>
	T min_left(T r){ return min_left<decltype(f)>(r,f); }
	template<class F>
	T min_left(T r,F f){
		assert(q[1].l<=r && r<=q[1].r);
		S s=e(); return max(q[1].l,_minl(r,f,s));
	}
	template<auto f>
	T max_right(T l){ return max_right<decltype(f)>(l,f); }
	template<class F>
	T max_right(T l,F f){
		assert(q[1].l<=l && l<=q[1].r);
		S s=e(); return min(q[1].r,_maxr(l,f,s));
	}
};
#undef PP
#undef ls
#undef rs

namespace def{ // example: cnt
	using S=int;
	S op(S a,S b){ // new s = a op b
		return a+b;
	}
	S e(){ // x op e() = e() op x = x
		return 0;
	}
	using SGT=_SGT<int,S,op,e>;
};
using def::SGT;
