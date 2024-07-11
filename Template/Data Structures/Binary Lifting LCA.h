vector<int>dep(n+1);
const int mx_p=log2(n)+2;
vector lca(n+1,vector<int>(mx_p));
auto dfs_init=[&](auto&& self,int u,int fa)->void{
	dep[u]=dep[fa]+1,lca[u][0]=fa;
	for(auto v:e[u]){
		if(v==fa) continue;
		self(self,v,u);
	}
};
dfs_init(dfs_init,root,0);
for(int p=1;p<mx_p;p++){
	for(int u=1;u<=n;u++){
		lca[u][p]=lca[lca[u][p-1]][p-1];
	}
}
auto LCA=[&](int u,int v)->int{
	if(dep[v]<dep[u]) swap(u,v);
	for(int p=mx_p-1;p>=0;p--){
		if(dep[lca[v][p]]>=dep[u]){
			v=lca[v][p];
		}
	}
	if(u==v) return u;
	for(int p=mx_p-1;p>=0;p--){
		if(lca[u][p]!=lca[v][p]){
			u=lca[u][p],
			v=lca[v][p];
		}
	}
	return lca[u][0];
};
