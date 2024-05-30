const int inf=INT_MAX; //inf可按需要修改
template<typename T> //T是int或者LL
class MF{ //Max Flow
private:
	struct edge{
		int v,nxt;
		T cap,flow;
	};
	vector<edge>e;
	vector<int>fir,dep,cur;
	int n,s,t; LL maxflow;
public:
	MF(){}
	MF(int n_){init(n_);}
	void init(int n_){//n个点，下标从1~n
		n=n_,maxflow=0;
		e.clear();
		fir.assign(n+1,-1);
	}
	void addedge(int u,int v,T w){
		e.push_back({v,fir[u],w,0});
		fir[u]=e.size()-1;
		e.push_back({u,fir[v],0,0});
		fir[v]=e.size()-1;
	}
	bool bfs(){
		queue<int>q; q.push(s);
		dep.assign(n+1,0); dep[s]=1;
		while(q.size()){
			int u=q.front(); q.pop();
			for(int i=fir[u];~i;i=e[i].nxt){
				int v=e[i].v;
				if((!dep[v])&&(e[i].cap>e[i].flow)){
					dep[v]=dep[u]+1;
					q.push(v);
				}
			}
		}
		return dep[t];
	}
	T dfs(int u,T flow){
		if ((u==t) || (!flow)) return flow;
		T ret=0;
		for(int &i=cur[u];~i;i=e[i].nxt){
			int v=e[i].v; T d;
			if ((dep[v] == dep[u] + 1) &&
				(d = dfs(v, min(flow - ret, e[i].cap - e[i].flow)))){
				ret+=d,e[i].flow+=d,e[i^1].flow-=d;
				if(ret==flow) return ret;
			}
		}
		return ret;
	}
	LL dinic(int s_,int t_){
		s=s_,t=t_;
		while(bfs()){
			cur=fir;
			maxflow+=dfs(s,inf);
		}
		return maxflow;
	}
};
