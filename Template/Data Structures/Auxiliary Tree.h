vector<int>adj[N]; //adj存虚树
int flag[N]; //flag判断是否是关键点

void solve(int col){
	int m=read();
	vector<int>a(m),b;
	for(int i=0;i<m;i++) flag[a[i]=read()]=col;
	if(flag[1]!=col) a.push_back(1),m++; //如果有需要的话，可以把根节点(1)放进虚树内
	sort(a.begin(),a.end(),cmp); //a中存关键点，按照dfn排序
	for(int i=0;i<m-1;i++){
		b.push_back(a[i]);
		b.push_back(LCA(a[i],a[i+1])); //插入关键点之间的lca
	}
	b.push_back(a.back()); //别忘了把最后一个点放进去
	sort(b.begin(),b.end(),cmp); //把所有虚树上的点按照dfn排序
	b.erase(unique(b.begin(),b.end()),b.end()); //去重
	for(int u:b) adj[u].clear(); //清空上一次的虚树
	for(int i=0;i<b.size()-1;i++){
		adj[LCA(b[i],b[i+1])].push_back(b[i+1]); //虚树连边
	}
	printf("%d\n",calc(1,col).first); //在虚树上处理出答案
}
