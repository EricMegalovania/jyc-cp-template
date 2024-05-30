//CF893F
const int inf=1e9;
class pSGT{//persistent SGT
private:
	struct Node{
		int ls,rs,mn;
	};
	vector<Node>q;
	void update(int id){
		q[id].cnt=min(q[q[id].ls].mn,q[q[id].rs].mn);
	}
	int build(const vector<int>& a,int l,int r){
		int id=q.size();
		q.push_back(Node{0,0,inf});
		if(l==r){
			q[id].mn=a[l];
			return id;
		}
		int mid=l+r>>1;
		q[id].ls=build(a,l,mid);
		q[id].rs=build(a,mid+1,r);
		update(id);
		return id;
	}
public:
	vector<int>root;
	pSGT(){
		init();
	}
	pSGT(const vector<int>& a,int n){
		init(a,n);
	}
	void init(){
		q.clear(),root.clear();
		q.push_back(Node{0,0,inf});
		root.push_back(0);
	}
	void init(const vector<int>& a,int n){
		q.clear(),root.clear();
		q.push_back(Node{0,0,inf});
		root.push_back(0);
		add_root(build(a,1,n));
	}
	void add_root(const int& x){
		root.push_back(x);
	}
	int insert(int id,int l,int r,int pos,int val){
		int new_id=q.size();
		q.push_back(q[id]);
		q[new_id].mn=min(q[id].mn,val);
		if(l!=r){
			int mid=l+r>>1;
			if(pos<=mid) q[new_id].ls=insert(q[id].ls,l,mid,pos,val);
			else q[new_id].rs=insert(q[id].rs,mid+1,r,pos,val);
		}
		return new_id;
	}
	//query [L,R]'s min, current Node id's range is [l,r]
	int find(int id,int L,int R,int l,int r){
		if(L==l && R==r) return q[id].mn;
		int mid=l+r>>1;
		if(R<=mid) return find(q[id].ls,L,R,l,mid);
		else if(L>mid) return find(q[id].rs,L,R,mid+1,r);
		else return min(find(q[id].ls,L,mid,l,mid),find(q[id].rs,mid+1,R,mid+1,r));
	}
};

int main(){
	int n=read(),root=read();
	vector<int>a(n+1);
	for(int i=1;i<=n;i++) a[i]=read();
	vector<vector<int>>e(n+1);
	for(int i=1,u,v;i<n;i++){
		u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	vector<int>dfn(n+1),dep(n+1),siz(n+1);
	int timStamp=0,max_dep=0;
	auto dfs=[&](auto self,int u,int fa)->void{
		dfn[u]=++timStamp,dep[u]=dep[fa]+1,siz[u]=1;
		max_dep=max(max_dep,dep[u]);
		for(int v:e[u]){
			if(v==fa) continue;
			self(self,v,u);
			siz[u]+=siz[v];
		}
	};
	dfs(dfs,root,0);
	vector<vector<int>>add(max_dep+1);
	for(int i=1;i<=n;i++){
		add[dep[i]].push_back(i);
	}
	vector<int>rt(max_dep+1);
	pSGT sgt;
	for(int i=1,tot=0;i<=max_dep;i++){
		for(int u:add[i]){
			sgt.add_root(sgt.insert(sgt.root[tot++],1,n,dfn[u],a[u]));
		}
		rt[i]=tot;
	}
	for(int T=read(),last=0,u,k;T--;){
		u=(read()+last)%n+1,k=(read()+last)%n;
		last=sgt.find(sgt.root[rt[min(max_dep,dep[u]+k)]],dfn[u],dfn[u]+siz[u]-1,1,n);
		printf("%d\n",last);
	}
	return 0;
}
