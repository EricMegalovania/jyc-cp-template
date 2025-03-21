vector<int>dfn(n+1),low(n+1),cut(n+1);
vector<vector<int>>dcc(1);
int root,timStamp=0;
stack<int,vector<int>>stk;
auto tarjan=[&](auto&& self,int u)->void{
	low[u]=dfn[u]=++timStamp;
	if(u==root && e[u].empty()){
		dcc.push_back({u});
		return;
	}
	stk.push(u);
	int flag=0;
	for(auto v:e[u]){
		if(!dfn[v]){
			self(self,v);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				flag++;
				if(u!=root || flag>1) cut[u]=1;
				dcc.push_back({});
				int trash;
				do{
					dcc.back().push_back(trash=stk.top());
					stk.pop();
				}while(trash!=v);
				dcc.back().push_back(u);
			}
		}
		else low[u]=min(low[u],dfn[v]); //这里dfn不能写成low
	}
};
for(int i=1;i<=n;i++){
	if(!dfn[i]){
		root=i;
		tarjan(tarjan,i);
	}
}
vector<int>new_id(n+1); int num=dcc.size();
for(int i=1;i<=n;i++){
	if(cut[i]) new_id[i]=num++;
}
vector<vector<int>>adj(num);
for(int i=1;i<dcc.size();i++){
	for(auto u:dcc[i]){
		if(cut[u]){
			adj[i].push_back(new_id[u]);
			adj[new_id[u]].push_back(i);
		}
		else new_id[u]=i;
	}
}
