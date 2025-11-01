#define N 20
int a[N]; LL dp[N][3];

// 从高位往低位记忆化搜索
// pos: cur-digit-pos, st: status, flag: can 0-9?
// st: 0,no4or38 | 1,no4or38,cur3 | 2,has4or38
LL dfs(int pos,int st,bool flag){
	if(!pos) return st==2;
	if(flag && dp[pos][st]!=-1) return dp[pos][st];
	int mxi=flag?9:a[pos];
	LL res=0;
	for(int i=0;i<=mxi;++i){
		if(st==2 || i==4 || (st==1 && i==8)){
			res+=dfs(pos-1,2,flag|(i!=mxi));
		}
		else if(i==3){
			res+=dfs(pos-1,1,flag|(i!=mxi));
		}
		else{
			res+=dfs(pos-1,0,flag|(i!=mxi));
		}
	}
	if(flag) dp[pos][st]=res;
	return res;
}
LL calc(LL x){
	if(x<0) return 0;
	int pos=0;
	while(x){
		a[++pos]=x%10;
		x/=10;
	}
	return dfs(pos,0,0);
}
void solve(){
	LL l,r;
	cin>>l>>r;
	cout<<calc(r)-calc(l-1)<<'\n';
}

memset(dp,-1,sizeof(dp));
