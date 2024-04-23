//火车头，娱乐用，用来平时做题凹卡常题
#pragma GCC target("avx")
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

//模板正式开始
#include<bits/stdc++.h>
using namespace std;

//#define ONLINE
#ifndef ONLINE
#define debug(...) fprintf(stderr,##__VA_ARGS__)
#else
#define debug(...) ;
#endif

using LL=long long;
using PII=pair<int,int>;

const int mod=998244353;

//double关键字比大小
#define eps (1e-8)
inline int sign(const double& x){
	if(fabs(x)<eps) return 0;
	return x>0.0?1:-1;
}
inline int dcmp(const double& x,const double& y){
	return sign(x-y);
}

//快读
template<typename T>
inline T READ(){
	T x=0; bool f=0; char c=getchar();
	while(c<'0' || c>'9') f|=(c=='-'),c=getchar();
	while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return f?-x:x;
}
inline int read(){return READ<int>();}
inline LL readLL(){return READ<LL>();}

//快速幂
LL ksm(LL a,LL b){
	a%=mod; LL ret=1;
	while(b){
		if(b&1) ret=ret*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ret;
}

//矩阵乘法
void mul(const vector<vector<LL>>& a,vector<LL>& f,int n){//f=a*f
	vector<LL>b(n,0);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			b[i]=(b[i]+a[i][j]*f[j]%mod)%mod;
		}
	}
	swap(f,b);
}
void self_mul(vector<vector<LL>>& a,int n){//a=a*a
	vector b(n,vector<LL>(n,0));
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				b[i][j]=(b[i][j]+a[i][k]*a[k][j]%mod)%mod;
			}
		}
	}
	swap(a,b);
}

#define N 100010

//线性筛欧拉函数
bool notP[N]={}; int phi[N],mn_p[N]={};
vector<int>prime;
void init_prime(const int& n=N){
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!notP[i]){
			prime.push_back(mn_p[i]=i);
			phi[i]=i-1;
		}
		for(int j=0;j<prime.size() && i*prime[j]<=n && i*prime[j]>0;j++){
			notP[i*prime[j]]=1,mn_p[i*prime[j]]=prime[j];
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}

//树状数组
template<typename T>//T is int or LL
class FenTree{
private:
	int n;
	vector<T>c;
	inline int lowbit(const int& x){
		return x&(-x);
	}
public:
	FenTree(int n_){
		c.assign(n=n_,T(0));
	}
	void init(int n_){
		c.assign(n=n_,T(0));
	}
	void add(int i,int x){
		for(;i<n;i+=lowbit(i)) c[i]+=x;
	}
	T query(int i){
		T res=0;
		for(;i;i-=lowbit(i)) res+=c[i];
		return res;
	}
};

//线段树
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
	void build(const vector<int>& a,int l,int r,int id=1){
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
	SGT(const vector<int>& a,int n){
		q.resize(n*5);
		build(a,1,n);
	}
	void init(const vector<int>& a,int n){
		q.resize(n*5);
		build(a,1,n);
	}
	void modify(int l,int r,int val,int id=1){
		if(q[id].l==l && q[id].r==r){
			//modify the value
			q[id].mx=val,q[id].tag=1;
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
		int mid=q[id].l+q[id].r>>1;
		if(pos<=mid) return get(pos,ls);
		return get(pos,rs);
	}
};
#undef ls
#undef rs

//树链剖分（重链剖分）
void heavy_path_decomposition(){
	//P3384【模板】重链剖分/树链剖分
	//this code can't be compiled
	//u need to put the following tepmplate in a FUNCTION!!!!!
	//also, remember to DELETE THE MOD in the template!!!!!
	int n=read(),T=read(),root=read();// mod=read();
	vector<int>a(n+1);
	for(int i=1;i<=n;i++) a[i]=read()%mod;//origin value
	vector<vector<int>>e(n+1);
	for(int i=1,u,v;i<n;i++){
		u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	vector<int>dep(n+1),fa(n+1),siz(n+1),son(n+1);
	auto dfs1=[&](auto self,int u,int pre)->void{
		dep[u]=dep[pre]+1,fa[u]=pre,siz[u]=1;
		for(int v:e[u]){
			if(v==pre) continue;
			self(self,v,u);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]]) son[u]=v;
		}
	};
	dfs1(dfs1,root,0);
	vector<int>id(n+1),nw(n+1),top(n+1);
	int timStamp=0;
	auto dfs2=[&](auto self,int u,int t)->void{
		id[u]=++timStamp,nw[timStamp]=u,top[u]=t;
		if(!son[u]) return;
		self(self,son[u],t);
		for(int v:e[u]){
			if(v==fa[u] || v==son[u]) continue;
			self(self,v,v);
		}
	};
	dfs2(dfs2,root,root);
	auto LCA=[&](int u,int v)->int{
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			u=fa[top[u]];
		}
		return dep[u]<dep[v]?u:v;
	};
	vector<int>sgt_init(n+1);
	for(int i=1;i<=n;i++) sgt_init[i]=a[nw[i]];
	SGT sgt(sgt_init,n);//sgt needs to support seg add, seg query
	auto modify_path=[&](int u,int v,LL val)->void{
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			sgt.modify(id[top[u]],id[u],val);
			u=fa[top[u]];
		}
		if(dep[u]<dep[v]) swap(u,v);
		sgt.modify(id[v],id[u],val);
	};
	auto query_path=[&](int u,int v)->LL{
		LL cnt=0ll;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			cnt+=sgt.query(id[top[u]],id[u]);
			u=fa[top[u]];
		}
		if(dep[u]<dep[v]) swap(u,v);
		cnt+=sgt.query(id[v],id[u]);
		return cnt%mod;
	};
	auto modify_tree=[&](int u,int val)->void{
		sgt.modify(id[u],id[u]+siz[u]-1,val);
	};
	auto query_tree=[&](int u)->LL{
		return sgt.query(id[u],id[u]+siz[u]-1);
	};
	for(int op,u,v,w;T--;){
		op=read(),u=read();
		if(op==1){
			v=read(),w=read();
			modify_path(u,v,w);
		}
		else if(op==2){
			v=read();
			printf("%lld\n",query_path(u,v));
		}
		else if(op==3){
			w=read();
			modify_tree(u,w);
		}
		else{//op==4
			printf("%lld\n",query_tree(u));
		}
	}
}

//平衡树 Warning: written 2 years ago, may have weird bug(s)
class fhqTreap{
private:
	struct Node{
		int l,r,siz,rnd,val;
	};
	vector<Node>q=vector<Node>(N);
	int nw,root,rootX,rootY,rootZ;
	int New(int val){
		q[nw++]={0,0,1,rand(),val};
		return nw;
	}
	void Update(int id){
		q[id].siz=q[q[id].l].siz+q[q[id].r].siz+1;
	}
	void Split(int id,int key,int& idX,int& idY){
		if(id==0){
			idX=idY=0;
			return;
		}
		if(q[id].val<=key){
			idX=id;
			Split(q[id].r,key,q[id].r,idY);
		}
		else{
			idY=id;
			Split(q[id].l,key,idX,q[id].l);
		}
		Update(id);
	}
	int Merge(int l,int r){
		if(l==0 || r==0) return l+r;
		if(q[l].rnd<=q[r].rnd){
			q[r].l=Merge(l,q[r].l);
			Update(r);
			return r;
		}
		else{
			q[l].r=Merge(q[l].r,r);
			Update(l);
			return l;
		}
	}
public:
	void Init(){
		root=nw=0;
	}
	void Insert(int val){
		Split(root,val,rootX,rootY);
		root=Merge(Merge(rootX,New(val)),rootY);
	}
	void Del(int val){
		Split(root,val,rootX,rootZ);
		Split(rootX,val-1,rootX,rootY);
		rootY=Merge(q[rootY].l,q[rootY].r);
		root=Merge(Merge(rootX,rootY),rootZ);
	}
	int Pre(int val){
		Split(root,val-1,rootX,rootY);
		int tmp=rootX;
		while(q[tmp].r) tmp=q[tmp].r;
		root=Merge(rootX,rootY);
		return q[tmp].val;
	}
	int Nxt(int val){
		Split(root,val,rootX,rootY);
		int tmp=rootY;
		while(q[tmp].l) tmp=q[tmp].l;
		root=Merge(rootX,rootY);
		return q[tmp].val;
	}
	int Rank(int val){//val's rank
		Split(root,val-1,rootX,rootY);
		int ans=q[rootX].siz+1;
		root=Merge(rootX,rootY);
		return ans;
	}
	int Get(int rank){
		int id=root;
		while(1){
//			printf("id:%d val:%d l:%d lsiz:%d r:%d rsiz:%d|rank:%d\n",id,q[id].val,q[id].l,q[q[id].l].siz,q[id].r,q[q[id].r].siz,rank);  
			if(q[q[id].l].siz>=rank) id=q[id].l;
			else if(q[q[id].l].siz+1==rank) return q[id].val;
			else{
				rank-=(q[q[id].l].siz+1);
				id=q[id].r;
			}
		}
	}
};

//字符串哈希（多重哈希）
namespace HASH_CONST{
	const int P[4]={13331,233,131,19260817};
	const int MOD[4]={(int)(1e9+7),998244353,1004535809,754974721};
	LL ksm[N][4];
	void init(int use=4){
		for(int j=0;j<use;j++){
			ksm[0][j]=1;
			for(int i=1;i<N;i++){
				ksm[i][j]=(ksm[i-1][j]*P[j])%MOD[j];
			}
		}
	}
}
template<int T>//T must be a constant
class Hash{
private:
	vector<array<LL,T>>h;
	bool sign;//0:normal 1:reverse
public:
	Hash(char *s,int n,bool sign_=0){
		init(s,n,sign_);
	}
	void init(char *s,int n,bool sign_=0){//s stores at pos [1,n], and just give para s (NOT s+1)
		h.resize(n+2);
		sign=sign_;
		if(!sign){
			for(int j=0;j<T;j++){
				h[0][j]=0;
				for(int i=1;i<=n;i++){
					h[i][j]=(h[i-1][j]*HASH_CONST::P[j]+s[i]-'a'+1)%HASH_CONST::MOD[j];
				}
			}
		}
		else{
			for(int j=0;j<T;j++){
				h[n+1][j]=0;
				for(int i=n;i>0;i--){
					h[i][j]=(h[i+1][j]*HASH_CONST::P[j]+s[i]-'a'+1)%HASH_CONST::MOD[j];
				}
			}
		}
	}
	array<LL,T>calc(const int& l,const int& r){
		array<LL,T>ret;
		if(!sign){
			for(int j=0;j<T;j++){
				ret[j]=h[r][j]-h[l-1][j]*HASH_CONST::ksm[r-l+1][j];
			}
		}
		else{
			for(int j=0;j<T;j++){
				ret[j]=h[l][j]-h[r+1][j]*HASH_CONST::ksm[r-l+1][j];
			}
		}
		for(int j=0;j<T;j++){
			ret[j]=(ret[j]%HASH_CONST::MOD[j]+HASH_CONST::MOD[j])%HASH_CONST::MOD[j];
		}
		return ret;
	}
	static bool check(const array<LL,T>& a,const array<LL,T>& b){
		for(int i=0;i<T;i++){
			if(a[i]!=b[i]) return 0;
		}
		return 1;
	}
};

//阶乘相关的初始化
namespace Fac{//factorial
	LL fc[N]={1},fc_inv[N]={1};
	void init(){
		for(int i=1;i<N;i++){
			fc[i]=fc[i-1]*i%mod;
			fc_inv[i]=fc_inv[i-1]*ksm(i,mod-2)%mod;
		}
	}
	LL F(const int& x){
		return fc[x];
	}
	LL P(const int& x,const int& y){
		return fc[x]*fc_inv[x-y]%mod;
	}
	LL C(const int& x,const int& y){
		return fc[x]*fc_inv[y]%mod*fc_inv[x-y]%mod;
	}
}

int main(){
	
	return 0;
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
