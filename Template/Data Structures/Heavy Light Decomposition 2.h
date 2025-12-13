vector<int>dep(n+1),fa(n+1),deep(n+1),son(n+1,-1);
auto dfs1=[&](auto&& self,int u,int pre)->void{
	dep[u]=dep[pre]+1,fa[u]=pre,deep[u]=dep[u];
	for(int v:e[u]){
		if(v==pre) continue;
		self(self,v,u);
		deep[u]=max(deep[u],deep[v]);
		if(son[u]==-1 || deep[v]>deep[son[u]]) son[u]=v;
	}
};
dfs1(dfs1,root,-1);
vector<int>id(n+1),nw(n+2),top(n+1);
int timStamp=0;
auto dfs2=[&](auto&& self,int u,int t)->void{
	id[u]=++timStamp,nw[timStamp]=u,top[u]=t;
	if(son[u]==-1) return;
	self(self,son[u],t);
	for(int v:e[u]){
		if(v==fa[u] || v==son[u]) continue;
		self(self,v,v);
	}
};
dfs2(dfs2,root,root);
