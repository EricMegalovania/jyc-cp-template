//P3834【模板】可持久化线段树 2
//区间静态查找第 k 小
const int inf=1e9;
class pSGT{//persistent SGT
private:
	struct Node{
		int ls,rs,cnt;
	};
	vector<Node>q;
public:
	vector<int>root;
	pSGT(){
		init();
	}
	void init(){
		q.clear(),root.clear();
		q.push_back(Node{});
		root.push_back(0);
	}
	void add_root(const int& x){
		root.push_back(x);
	}
	int insert(int id,int l,int r,int val){
		int new_id=q.size();
		q.push_back(q[id]);
		q[new_id].cnt++;
		if(l!=r){
			int mid=l+r>>1;
			if(val<=mid) q[new_id].ls=insert(q[id].ls,l,mid,val);
			else q[new_id].rs=insert(q[id].rs,mid+1,r,val);
		}
		return new_id;
	}
	int find(int idL,int idR,int l,int r,int k){
		if(l==r) return l;
		int mid=l+r>>1;
		int lcnt=q[q[idR].ls].cnt-q[q[idL].ls].cnt;
		if(k<=lcnt) return find(q[idL].ls,q[idR].ls,l,mid,k);
		else return find(q[idL].rs,q[idR].rs,mid+1,r,k-lcnt);
	}
};

int main(){
	int n=read(),T=read();
	pSGT sgt;
	for(int i=1;i<=n;i++){
		sgt.add_root(sgt.insert(sgt.root[i-1],0,inf,read()));
	}
	for(int l,r;T--;){
		l=read(),r=read();
		printf("%d\n",sgt.find(sgt.root[l-1],sgt.root[r],0,inf,read()));
	}
	return 0;
}
