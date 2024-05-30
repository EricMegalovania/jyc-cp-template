using PLL=pair<LL,LL>;
const int inf=INT_MAX; //inf可按需要修改
//T是int或者LL; sign: 0=最小费用, 1=最大费用
template<typename T>
class MCMF{ //Min Cost Max Flow
private:
	struct edge{
		int v,nxt;
		T cap,flow,cost;
	};
	vector<edge>e;
	vector<int>fir,cur,vis;
	vector<LL>dis;
	int n,s,t; bool sign;
	LL total_cost,maxflow;
public:
	MCMF(){}
	MCMF(int n_){init(n_);}
	void init(int n_){//n个点，下标从1~n
		n=n_,total_cost=maxflow=0;
		e.clear();
		fir.assign(n+1,-1);
		vis.assign(n+1,0);
	}
	void addedge(int u,int v,T w,T c){
		e.push_back({v,fir[u],w,0,c});
		fir[u]=e.size()-1;
		e.push_back({u,fir[v],0,0,-c});
		fir[v]=e.size()-1;
	}
	bool spfa(){
		dis.assign(n+1,sign?-inf:inf),cur=fir;
		queue<int>q;
		q.push(s),dis[s]=0,vis[s]=1;
		while(q.size()){
			int u=q.front(); q.pop();
			vis[u]=0;
			for(int i=fir[u];~i;i=e[i].nxt){
				int v=e[i].v;
				if((e[i].cap>e[i].flow) &&
					(sign?(dis[v]<dis[u]+e[i].cost):(dis[v]>dis[u]+e[i].cost))){
					dis[v]=dis[u]+e[i].cost;
					if(!vis[v]){
						q.push(v),vis[v]=1;
					}
				}
			}
		}
		return dis[t]!=(sign?-inf:inf);
	}
	T dfs(int u,T flow){
		if ((u==t) || (!flow)) return flow;
		T ret=0; vis[u]=1;
		for(int &i=cur[u];~i;i=e[i].nxt){
			int v=e[i].v; T d;
			if (!vis[v] && dis[v]==dis[u]+e[i].cost &&
				(d = dfs(v, min(flow - ret, e[i].cap - e[i].flow)))){
				total_cost+=1ll*d*e[i].cost,ret+=d,
				e[i].flow+=d,e[i^1].flow-=d;
				if(ret==flow){
					vis[u]=0;
					return ret;
				}
			}
		}
		vis[u]=0;
		return ret;
	}
	//sign: 0=min_cost, 1=max_cost
	PLL dinic(int s_,int t_,const bool& sign_=0){
		s=s_,t=t_,sign=sign_;
		while(spfa()){
			T x;
			while((x=dfs(s,inf))){
				maxflow+=x;
			}
		}
		return {maxflow,total_cost};
	}
};
