const int inf_f=INT_MAX;
const LL inf_c=LLONG_MAX;
template<typename T1,typename T2> //T1:flow type, T2:cost type
class MCMF{ //Min Cost Max Flow
private:
	struct edge{
		int v,nxt;
		T1 f; T2 c;
	};
	vector<edge>e;
	vector<int>head,vis;
	vector<T2>dis,h;
	vector<array<int,2>>opt; //{pre_node_id,edge_id} record path
	int n,s,t;
	T1 maxf; T2 minc;
	void spfa(){
		queue<int>q;
		h.assign(n+1,inf_c),vis.assign(n+1,0);
		q.push(s),h[s]=0,vis[s]=1;
		while(q.size()){
			int u=q.front(); q.pop();
			vis[u]=0;
			for(int i=head[u];~i;i=e[i].nxt){
				int v=e[i].v;
				if(e[i].f && h[v]>h[u]+e[i].c){
					h[v]=h[u]+e[i].c;
					if(!vis[v]){
						vis[v]=1;
						q.push(v);
					}
				}
			}
		}
	}
	bool dijkstra(){
		using PTI=pair<T2,int>;
		priority_queue<PTI,vector<PTI>,greater<>>q;
		dis.assign(n+1,inf_c),vis.assign(n+1,0);
		q.push({dis[s]=T2(0),s});
		while(q.size()){
			int u=q.top().second; q.pop();
			if(vis[u]) continue;
			vis[u]=1;
			for(int i=head[u];~i;i=e[i].nxt){
				int v=e[i].v;
				T2 nc=e[i].c+h[u]-h[v];
				if(e[i].f && dis[v]>dis[u]+nc){
					dis[v]=dis[u]+nc;
					opt[v]={u,i};
					if(!vis[v]) q.push({dis[v],v});
				}
			}
		}
		return dis[t]!=inf_c;
	}
public:
	MCMF(){}
	MCMF(int n_){init(n_);}
	void init(int n_){//n个点，下标从1~n
		n=n_;
		e.clear();
		head.assign(n+1,-1);
		opt.assign(n+1,{});
	}
	edge get(int id){return e[id];}
	void addedge(int u,int v,T1 w,T2 c){
		e.push_back({v,head[u],w,c});
		head[u]=e.size()-1;
		e.push_back({u,head[v],0,-c});
		head[v]=e.size()-1;
	}
	pair<T1,T2>dinic(int s_,int t_){
		s=s_,t=t_;
		maxf=T1(0),minc=T2(0);
		spfa(); //先求出初始势能
		while(dijkstra()){
			T1 minf=inf_f;
			for(int i=1;i<=n;i++) h[i]+=dis[i];
			for(int i=t;i!=s;i=opt[i][0]){
				minf=min(minf,e[opt[i][1]].f);
			}
			for(int i=t;i!=s;i=opt[i][0]){
				e[opt[i][1]].f-=minf;
				e[opt[i][1]^1].f+=minf;
			}
			maxf+=minf;
			minc+=h[t]*minf;
		}
		return {maxf,minc};
	}
};
