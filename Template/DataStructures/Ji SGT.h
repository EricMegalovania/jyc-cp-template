#include<bits/stdc++.h>
using namespace std;

using LL=long long;

const int inf=INT_MAX;
#define ls (id<<1)
#define rs (id<<1|1)
#define SPREAD_ID spread(id,q[id].l,q[id].r)

#define MODIFY(FUNC) \
SPREAD_ID; \
int mid=q[id].l+q[id].r>>1; \
if(r<=mid) FUNC(l,r,val,ls); \
else if(l>mid) FUNC(l,r,val,rs); \
else FUNC(l,mid,val,ls),FUNC(mid+1,r,val,rs); \
q[id]=q[ls]+q[rs]

#define ADD(A,B) A+B
#define QUERY(FUNC,QRY_FUNC) \
SPREAD_ID;\
int mid=q[id].l+q[id].r>>1; \
if(r<=mid) return FUNC(l,r,ls); \
else if(l>mid) return FUNC(l,r,rs); \
else return QRY_FUNC(FUNC(l,mid,ls),FUNC(mid+1,r,rs))

class JiSGT{
private:
	struct Node{
		int l,r;
		//count_max, count_min, tag_max, tag_min, tag_add
		int mx,mx2,mn,mn2,cmx,cmn,tmx,tmn,tad;
		LL sum;
		friend Node operator +(const Node& A,const Node& B){
			Node ret;
			ret.l=A.l,ret.r=B.r;
			ret.sum = A.sum + B.sum;
			if (A.mx == B.mx) {
				ret.mx = A.mx, ret.cmx = A.cmx + B.cmx;
				ret.mx2 = max(A.mx2, B.mx2);
			} else if (A.mx > B.mx) {
				ret.mx = A.mx, ret.cmx = A.cmx;
				ret.mx2 = max(A.mx2, B.mx);
			} else {
				ret.mx = B.mx, ret.cmx = B.cmx;
				ret.mx2 = max(A.mx, B.mx2);
			}
			if (A.mn == B.mn) {
				ret.mn = A.mn, ret.cmn = A.cmn + B.cmn;
				ret.mn2 = min(A.mn2, B.mn2);
			} else if (A.mn < B.mn) {
				ret.mn = A.mn, ret.cmn = A.cmn;
				ret.mn2 = min(A.mn2, B.mn);
			} else {
				ret.mn = B.mn, ret.cmn = B.cmn;
				ret.mn2 = min(A.mn, B.mn2);
			}
			ret.tmx=-inf, ret.tmn=inf, ret.tad=0;
			return ret;
		}
	};
	vector<Node>q;
	void spread_add(int id, int l, int r, int v) {
		// 更新加法标记的同时，更新 $\min$ 和 $\max$ 标记
		q[id].sum += (r - l + 1ll) * v;
		q[id].mx += v, q[id].mn += v;
		if (q[id].mx2 != -inf) q[id].mx2 += v;
		if (q[id].mn2 != inf) q[id].mn2 += v;
		if (q[id].tmx != -inf) q[id].tmx += v;
		if (q[id].tmn != inf) q[id].tmn += v;
		q[id].tad += v;
	}
	void spread_min(int id, int tg) {
		// 注意比较 $\max$ 标记
		if (q[id].mx <= tg) return;
		q[id].sum += (tg * 1ll - q[id].mx) * q[id].cmx;
		if (q[id].mn2 == q[id].mx) q[id].mn2 = tg;  // !!!
		if (q[id].mn == q[id].mx) q[id].mn = tg;    // !!!!!
		if (q[id].tmx > tg) q[id].tmx = tg;        // 更新取 $\max$ 标记
		q[id].mx = tg, q[id].tmn = tg;
	}
	void spread_max(int id, int tg) {
		if (q[id].mn > tg) return;
		q[id].sum += (tg * 1ll - q[id].mn) * q[id].cmn;
		if (q[id].mx2 == q[id].mn) q[id].mx2 = tg;
		if (q[id].mx == q[id].mn) q[id].mx = tg;
		if (q[id].tmn < tg) q[id].tmn = tg;
		q[id].mn = tg, q[id].tmx = tg;
	}
	void spread(int id,int l,int r){
		if(q[id].l==q[id].r) return;
		int mid=l+r>>1;
		if (q[id].tad){
			spread_add(ls, l, mid, q[id].tad);
			spread_add(rs, mid + 1, r, q[id].tad);
		}
		if (q[id].tmx != -inf){
			spread_max(ls, q[id].tmx);
			spread_max(rs, q[id].tmx);
		}
		if (q[id].tmn != inf){
			spread_min(ls, q[id].tmn);
			spread_min(rs, q[id].tmn);
		}
		q[id].tmx = -inf, q[id].tmn = inf, q[id].tad = 0;
	}
	void build(const vector<int>& a,int l,int r,int id=1){
		if(l==r){
			q[id].l=l,q[id].r=r;
			q[id].sum=q[id].mx = q[id].mn = a[l];
			q[id].mx2=-inf, q[id].mn2 = inf;
			q[id].cmx=q[id].cmn = 1;
			q[id].tmx=-inf, q[id].tmn = inf, q[id].tad=0;
			return;
		}
		int mid=l+r>>1;
		build(a,l,mid,ls);
		build(a,mid+1,r,rs);
		q[id]=q[ls]+q[rs];
	}
public:
	JiSGT(const vector<int>& a,int n){
		q.resize(n*4);
		build(a,1,n);
	}
	void init(const vector<int>& a,int n){
		q.resize(n*4);
		build(a,1,n);
	}
	void add(int l,int r,int val,int id=1){
		if(q[id].l==l && q[id].r==r){
			return spread_add(id,l,r,val);
		}
		MODIFY(add);
	}
	void tomin(int l,int r,int val,int id=1){
		if(r<q[id].l || l>q[id].r || q[id].mx<=val) return;
		if(l<=q[id].l && q[id].r<=r && q[id].mx2<val){
			return spread_min(id,val);
		}
		MODIFY(tomin);
	}
	void tomax(int l,int r,int val,int id=1){
		if(r<q[id].l || l>q[id].r || q[id].mn>=val) return;
		if(l<=q[id].l && q[id].r<=r && q[id].mn2>val){
			return spread_max(id,val);
		}
		MODIFY(tomax);
	}
	LL qsum(int l,int r,int id=1){
		if(q[id].l==l && q[id].r==r) return q[id].sum;
		QUERY(qsum,ADD);
	}
	LL qmax(int l,int r,int id=1){
		if(q[id].l==l && q[id].r==r) return q[id].mx;
		QUERY(qmax,max);
	}
	LL qmin(int l,int r,int id=1){
		if(q[id].l==l && q[id].r==r) return q[id].mn;
		QUERY(qmin,min);
	}
};
#undef ls
#undef rs
#undef SPREAD_ID
#undef MODIFY
#undef ADD
#undef QUERY
