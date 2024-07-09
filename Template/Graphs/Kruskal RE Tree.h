//此时只读完了 n, m
vector<array<int,3>>edge(m);
for(auto& [u,v,w]:edge){
	u=read(),v=read(),w=read();
}
sort(all(edge),[&](const array<int,3>& A,const array<int,3>& B)->bool{
	return A[2]<B[2]; //小于：最小生成树 大于：最大生成树
});
//因为会动态加点，用dsu板子不方便
vector<int>fa(n+1); iota(fa.begin(),fa.end(),0);
auto find=[&](int x)->int{
	while(x!=fa[x]) x=fa[x]=fa[fa[x]];
	return x;
};
vector<int>val(n+1);
vector<vector<int>>e(n+1);
int tot=n; //tot 是重构树的点数
for(auto [u,v,w]:edge){
	int fau=find(u),fav=find(v);
	if(fau==fav) continue;
	tot++;
	val.push_back(w);
	fa[fau]=fa[fav]=tot;
	fa.push_back(tot);
	e[fau].push_back(tot),
	e[fav].push_back(tot);
	e.push_back({fau,fav});
}
vector<int>dep(tot+1);
const int mx_p=log2(tot)+2;
vector lca(tot+1,vector<int>(mx_p));
auto dfs_init=[&](auto&& self,int u,int fa)->void{
	dep[u]=dep[fa]+1,lca[u][0]=fa;
	for(int v:e[u]){
		if(v==fa) continue;
		self(self,v,u);
	}
};
for(int i=tot;i>0;i--){
	if(!dep[i]) dfs_init(dfs_init,i,0);
}
for(int p=1;p<mx_p;p++){
	for(int u=1;u<=tot;u++){
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
//询问 u,v 的所有路径中 路径中最小边权的最大值
//or 路径中最大边权的最小值
for(int T=read(),u,v;T--;){
	u=read(),v=read();
	if(find(u)!=find(v)){
		printf("-1\n");
		continue;
	}
	printf("%d\n",val[LCA(u,v)]);
}
