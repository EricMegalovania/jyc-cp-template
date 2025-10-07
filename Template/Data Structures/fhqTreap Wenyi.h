template<typename T>
class fhqTreap{
private:
	struct Node{
		int l,r,siz; LL rnd;
		T val; bool lazy;
		Node(){
			l=r=siz=lazy=0;
			rnd=0ll; val=T(0);
		}
		Node(int l_,int r_,int siz_,LL rnd_,T val_){
			l=l_,r=r_,siz=siz_,lazy=0;
			rnd=rnd_; val=val_;
		}
	};
	vector<Node>q;
	int root,rootX,rootY,rootZ;
	int New(T val){
		Node new_node=Node(0,0,1,rng(),val);
		q.push_back(new_node);
		return q.size()-1;
	}
	void update(int id){
		q[id].siz=q[q[id].l].siz+q[q[id].r].siz+1;
	}
	void spread(int id){
		if(!id) return;
		if(q[id].lazy){
			q[q[id].l].lazy^=1;
			q[q[id].r].lazy^=1;
			swap(q[id].l,q[id].r);
			q[id].lazy=0;
		}
	}
	void split(int id,int key,int& x,int& y){
		if(id==0){
			x=y=0;
			return;
		}
		spread(id);
		if(q[q[id].l].siz+1<=key){
			x=id;
			split(q[id].r,key-q[q[id].l].siz-1,q[id].r,y);
		}
		else{
			y=id;
			split(q[id].l,key,x,q[id].l);
		}
		update(id);
	}
	int merge(int l,int r){
		if(l==0 || r==0) return l+r;
		if(q[l].rnd<=q[r].rnd){
			spread(r);
			q[r].l=merge(l,q[r].l);
			update(r);
			return r;
		}
		else{
			spread(l);
			q[l].r=merge(q[l].r,r);
			update(l);
			return l;
		}
	}
	void print(vector<T>&a,int u){
		if(!u) return;
		spread(u);
		print(a,q[u].l);
		a.push_back(q[u].val);
		print(a,q[u].r);
	}
public:
	fhqTreap(){
		init();
	}
	void init(){
		root=0; q.clear();
		Node empty_node=Node();
		q.push_back(empty_node);
	}
	void insert(T x){
		root=merge(root,New(x));
	}
	void reverse(int l,int r){
		split(root,l-1,rootX,rootZ);
		split(rootZ,r-l+1,rootY,rootZ);
		q[rootY].lazy^=1;
		root=merge(merge(rootX,rootY),rootZ);
	}
	T get(int rank){
		int id=root;
		while(1){
			spread(id);
			if(q[q[id].l].siz>=rank) id=q[id].l;
			else if(q[q[id].l].siz+1==rank) return q[id].val;
			else{
				rank-=(q[q[id].l].siz+1);
				id=q[id].r;
			}
		}
	}
	void to_ary(vector<T>&a){
		a.clear();
		print(a,root);
	}
};
