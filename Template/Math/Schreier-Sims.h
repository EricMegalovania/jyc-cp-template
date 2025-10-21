int rcnt[N];
vector<int> r[N][N], invr[N][N];
vector<vector<int>> t[N];
inline vector<int> operator * (const vector<int> &lhs, const vector<int> &rhs){
	vector<int> res(n);
	for (int i = 0; i < n; ++i)
		res[i] = lhs[rhs[i]];
	return res;
}
inline void dfs(int u, const vector<int> &);
inline void init(){
	for (int i = 0; i < n; ++i)
	{
		++rcnt[i];
		r[i][i].resize(n), invr[i][i].resize(n);
		for (int j = i; j < n; ++j)
			r[i][i][j] = invr[i][i][j] = j;
	}
}
inline bool contain(int u, const vector<int> &g){
	if (u == n)
		return true;
	int v = g[u];
	if (r[u][v].empty())
		return false;
	return contain(u + 1, invr[u][v] * g);
}
inline void add(int u, const vector<int> &g){
	if (contain(u, g))
		return;
	t[u].push_back(g);
	vector<int> h(n);
	for (int v = u; v < n; ++v)
		if (!r[u][v].empty())
			dfs(u, g * r[u][v]);
}
inline void dfs(int u, const vector<int> &g){
	int v = g[u];
	if (!r[u][v].empty())
		add(u + 1, invr[u][v] * g);
	else
	{
		++rcnt[u];
		r[u][v].resize(n), invr[u][v].resize(n);
		for (int w = u; w < n; ++w)
			invr[u][v][r[u][v][w] = g[w]] = w;
		for (auto f : t[u])
			dfs(u, f * g);
	}
}
