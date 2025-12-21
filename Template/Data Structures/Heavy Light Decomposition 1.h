vector<int>dep(n+1),fa(n+1),siz(n+1),son(n+1,-1);
auto dfs1=[&](auto&& self,int u,int pre)->void {
	if(pre!=-1) dep[u]=dep[pre]+1;
	fa[u]=pre,siz[u]=1;
	for(auto v:e[u]){
		if(v==pre) continue;
		self(self,v,u);
		siz[u]+=siz[v];
		if(son[u]==-1 || siz[v]>siz[son[u]]) son[u]=v;
	}
};
dfs1(dfs1,root,-1);
vector<int>dfn(n+1),dfn_inv(n+2),top(n+1);
int timStamp=0;
auto dfs2=[&](auto&& self,int u,int t)->void {
	dfn[u]=++timStamp,dfn_inv[timStamp]=u,top[u]=t;
	if(son[u]==-1) return;
	self(self,son[u],t);
	for(auto v:e[u]){
		if(v==fa[u] || v==son[u]) continue;
		self(self,v,v);
	}
};
dfs2(dfs2,root,root);
auto LCA=[&](int u,int v)->int {
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
};
vector<int>sgt_init(n+1);
for(int i=1;i<=n;i++) sgt_init[i]=a[dfn_inv[i]];
SGT sgt(sgt_init,n);//sgt needs to support seg add, seg query
auto modify_path=[&](int u,int v,LL val)->void {
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		sgt.modify(dfn[top[u]],dfn[u],val);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	sgt.modify(dfn[v],dfn[u],val);
};
auto query_path=[&](int u,int v)->LL {
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
auto modify_tree=[&](int u,int val)->void {
	sgt.modify(dfn[u],dfn[u]+siz[u]-1,val);
};
auto query_tree=[&](int u)->LL {
	return sgt.query(dfn[u],dfn[u]+siz[u]-1);
};
