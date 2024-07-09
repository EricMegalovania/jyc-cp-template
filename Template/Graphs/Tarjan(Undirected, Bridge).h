struct Edge{
	int v,nxt;
};
//现在只读完了 n, m
vector<Edge>e(2);
vector<int>h(n+1);
auto addedge=[&](int u,int v)->void{
	e.push_back({v,h[u]});
	h[u]=e.size()-1;
};
for(int i=1,u,v;i<=m;i++){
	u=read(),v=read();
	addedge(u,v);
	addedge(v,u);
}
vector<int>dfn(n+1),low(n+1),bridge(e.size(),0);
int timStamp=0;
auto tarjan=[&](auto&& self,int u,int in_edge)->void{
	dfn[u]=low[u]=++timStamp;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(!dfn[v]){
			self(self,v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				bridge[i]=bridge[i^1]=1;
			}
		}
		else if(i!=(in_edge^1)){
			low[u]=min(low[u],dfn[v]);
		}
	}
};
for(int i=1;i<=n;i++){
	if(!dfn[i]){
		tarjan(tarjan,i,0);
	}
}
vector<int>col(n+1); int nwCol=0;
auto dfs=[&](auto&& self,int u)->void{
	col[u]=nwCol;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(col[v] || bridge[i]) continue;
		self(self,v);
	}
};
for(int i=1;i<=n;i++){
	if(!col[i]){
		++nwCol;
		dfs(dfs,i);
	}
}
vector<int>siz(nwCol+1);
vector<vector<int>>adj(nwCol+1);
for(int u=1;u<=n;u++){
	siz[col[u]]++;
	for(int i=h[u];i;i=e[i].nxt){
		if(bridge[i]){
			adj[col[u]].push_back(col[e[i].v]);
			adj[col[e[i].v]].push_back(col[u]);
		}
	}
}
for(int i=1;i<=nwCol;i++){
	sort(all(adj[i]));
	adj[i].erase(unique(all(adj[i])),adj[i].end());
}
