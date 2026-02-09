template<int N>
struct KM{
	bitset<N>e[N],nvis,nw;
	int L[N],R[N];  // 左边的 i 匹配右边的 L[i], 左边的 R[i] 匹配右边的 i
	int p[N],d[N];  // p: 记录增广路, d: 距离标记
	int pre[N];     // 增广路上, 右边的 i 的上一个点是左边的 pre[i]
	int n,m;        // 点的编号: 左边 [0,n-1], 右边 [0,m-1]
	KM(int l=0,int r=0){ init(l,r); }
	void init(int l,int r){ n=l,m=r; clear(); }
	void clear(){
		memset(L,-1,sizeof(L));
		memset(R,-1,sizeof(R));
		for(int i=0;i<n;++i) e[i].reset();
	}
	void addedge(int u,int v){ e[u][v]=1; }
	int max_match(){
		memset(p,-1,sizeof(p));
		memset(pre,-1,sizeof(pre));
		int res=0;
		auto bfs=[&](int st)->bool {
			memset(d,-1,sizeof(d)); d[st]=0;
			queue<int>q; q.push(st);
			nvis.set();
			while(!q.empty()){
				int u=q.front(); q.pop();
				nw=e[u]&nvis;
				for(int v=nw._Find_first();v<m;v=nw._Find_next(v)) {
					nvis.reset(v);
					pre[v]=u;
					if(R[v]==-1){
						while(v!=-1){ R[v]=pre[v]; swap(v,L[pre[v]]); }
						return 1;
					}
					q.push(R[v]);
				}
			}
			return 0;
		};
		for(int u=0;u<n;++u) if(bfs(u)) ++res;
		return res;
	}
};