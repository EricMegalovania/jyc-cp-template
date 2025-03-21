//#define HLD_SGT
struct HLD{
	vector<int>dep,fa,siz,son;
	vector<int>dfn,dfn_inv,top;
#ifdef HLD_SGT
	vector<int>sgt_init;
	SGT sgt;
#endif
	int root;
	HLD(){}
	HLD(const auto& e,int n,int rt=1){init(n,rt);}
	void init(const auto& e,int n,int rt=1){
		root=rt;
		dep.resize(n+1),fa.resize(n+1),
		siz.resize(n+1),son.resize(n+1);
		auto dfs1=[&](auto&& self,int u,int pre)->void{
			dep[u]=dep[pre]+1,fa[u]=pre,siz[u]=1;
			for(auto v:e[u]){
				if(v==pre) continue;
				self(self,v,u);
				siz[u]+=siz[v];
				if(siz[v]>siz[son[u]]) son[u]=v;
			}
		};
		dfs1(dfs1,root,0);
		dfn.resize(n+1),dfn_inv.resize(n+1),top.resize(n+1);
		int timStamp=0;
		auto dfs2=[&](auto&& self,int u,int t)->void{
			dfn[u]=++timStamp,dfn_inv[timStamp]=u,top[u]=t;
			if(!son[u]) return;
			self(self,son[u],t);
			for(auto v:e[u]){
				if(v==fa[u] || v==son[u]) continue;
				self(self,v,v);
			}
		};
		dfs2(dfs2,root,root);
#ifdef HLD_SGT
		sgt_init.resize(n+1);
		for(int i=1;i<=n;i++) sgt_init[i]=a[dfn_inv[i]];
		SGT sgt.init(sgt_init,n);//sgt needs to support seg add, seg query
#endif
	}
	int LCA(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			u=fa[top[u]];
		}
		return dep[u]<dep[v]?u:v;
	};
	int dist(int u,int v){ //edges
		return dep[u]+dep[v]-dep[LCA(u,v)]*2;
	}
#ifdef HLD_SGT
	void modify_path(int u,int v,LL val){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			sgt.modify(dfn[top[u]],dfn[u],val);
			u=fa[top[u]];
		}
		if(dep[u]<dep[v]) swap(u,v);
		sgt.modify(dfn[v],dfn[u],val);
	};
	LL query_path(int u,int v){
		LL cnt=0ll;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			cnt+=sgt.query(dfn[top[u]],dfn[u]);
			u=fa[top[u]];
		}
		if(dep[u]<dep[v]) swap(u,v);
		cnt+=sgt.query(dfn[v],dfn[u]);
		return cnt;
	};
	void modify_tree(int u,int val){
		sgt.modify(dfn[u],dfn[u]+siz[u]-1,val);
	}
	LL query_tree(int u){
		return sgt.query(dfn[u],dfn[u]+siz[u]-1);
	}
#endif
};
