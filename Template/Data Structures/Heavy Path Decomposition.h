//P3384, remember to erase the mod
void heavy_path_decomposition(){
	int n=read(),T=read(),root=read(),mod=read();
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
