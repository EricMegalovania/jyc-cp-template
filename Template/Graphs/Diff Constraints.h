/*
let d[0] be virtual S, d[0]=0.
graph is 1-based-index.
d[x]-d[y]<=c : addineq(x,y,c)
d[x]-d[y]>=c : addineq(y,x,-c)
d[x]-d[y]==c : addineq(x,y,c), addineq(y,x,-c)
d[x]==d[y] : addineq(x,y,0), addineq(y,x,0)
default: -hinf<=d[x]<=hinf
if, l<=d[x]<=r:
- d[x]-d[0]>=l, addineq(0,x,-l)
- d[x]-d[0]<=r, addineq(x,0,r)
*/
constexpr LL inf=2e18;
constexpr LL hinf=inf/2; // half inf
struct DC{ // diff-constraints
	int n;
	vector<bool>vis;
	vector<int>cnt;
	vector<LL>dis,L,R;
	vector<vector<pair<int,LL>>>e;
	DC(){}
	DC(int n_){init(n_);}
	void init(int n_){
		n=n_;
		L.assign(n+1,-hinf);
		R.assign(n+1,hinf);
		e.assign(n+1,{});
	}
	void addineq(int x,int y,LL c){ // d[x]-d[y]<=c
		e[y].emplace_back(x,c);
	}
	void setx(int x,LL l,LL r){ // l<=x<=r
		L[x]=l,R[x]=r;
	}
	bool spfa(){
		vis.assign(n+1,0);
		cnt.assign(n+1,0);
		dis.assign(n+1,inf);
		dis[0]=0,vis[0]=1;
		queue<int>p; p.push(0);
		while(p.size()){
			int u=p.front();
			p.pop(),vis[u]=0;
			for(auto& [v,w]:e[u]){
				if(updmn(dis[v],dis[u]+w)){
					cnt[v]=cnt[u]+1;
					if(cnt[v]>=n+1) return 0;
					if(!vis[v]) p.push(v),vis[v]=1;
				}
			}
		}
		return 1;
	}
	bool check(){
		for(int i=1;i<=n;++i){
			addineq(0,i,-L[i]);
			addineq(i,0,R[i]);
		}
		return spfa();
	}
};
