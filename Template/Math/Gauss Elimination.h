// n 为未知数个数，m 为方程个数，返回方程组的解
// (多解 / 无解返回一个空的 vector)
bitset<N>mt[N]; //mt[1~n]：增广矩阵，0 位置为常数
vector<bool>GElim(int n, int m){// Gauss Elimination
	for(int i=1;i<=n;i++){
		int cur=i;
		while(cur<=m && !mt[cur][i]) cur++;
		if(cur>m){
//			if(mt[i][0]){
			return vector<bool>(0);
//			}
//			else continue;
		}
		if(cur!=i) swap(mt[cur],mt[i]);
		for(int j=1;j<=m;j++){
			if(i!=j && mt[j][i]) mt[j]^=mt[i];
		}
	}
	vector<bool>ans(n+1);
	for(int i=1;i<=n;i++) ans[i]=mt[i][0];
	return ans;
}
