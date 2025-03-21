int n;
vector<int>e[N];
bitset<N>vis=0;

int siz[N],tot;
void size(int u,int fa){
	++tot,siz[u]=1;
	for(auto v:e[u]) if(!vis[v] && v!=fa){
		size(v,u);
		siz[u]+=siz[v];
	}
}
int f[N],root;
void dp(int u,int fa){
	f[u]=tot-siz[u];
	for(auto v:e[u]) if(!vis[v] && v!=fa){
		updmx(f[u],siz[v]);
		dp(v,u);
	}
	if(f[u]<f[root]) root=u;
}
void calc(int u){
	tot=0; size(u,0);
	root=u; dp(u,0);
	for(auto v:e[root]) if(!vis[v]){
		//modify this
	}
	vis[root]=1;
	for(auto v:e[root]) if(!vis[v]){
		calc(v);
	}
}

int main(){
	cin>>n;
	for(int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	calc(1);
	return 0;
}
