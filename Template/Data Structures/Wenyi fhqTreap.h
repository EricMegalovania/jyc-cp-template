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
	void Update(int id){
		q[id].siz=q[q[id].l].siz+q[q[id].r].siz+1;
	}
	void Spread(int id){
		if(!id) return;
		if(q[id].lazy){
			q[q[id].l].lazy^=1;
			q[q[id].r].lazy^=1;
			swap(q[id].l,q[id].r);
			q[id].lazy=0;
		}
	}
	void Split(int id,T key,int& idX,int& idY){
		if(id==0){
			idX=idY=0;
			return;
		}
		Spread(id);
		if(q[q[id].l].siz+1<=key){
			idX=id;
			Split(q[id].r,key-q[q[id].l].siz-1,q[id].r,idY);
		}
		else{
			idY=id;
			Split(q[id].l,key,idX,q[id].l);
		}
		Update(id);
	}
	int Merge(int l,int r){
		if(l==0 || r==0) return l+r;
		if(q[l].rnd<=q[r].rnd){
			Spread(r);
			q[r].l=Merge(l,q[r].l);
			Update(r);
			return r;
		}
		else{
			Spread(l);
			q[l].r=Merge(q[l].r,r);
			Update(l);
			return l;
		}
	}
	void Print(vector<int>&a,int u){
		if(!u) return;
		Spread(u);
		Print(a,q[u].l);
		a.push_back(q[u].val);
		Print(a,q[u].r);
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
	void insert(int x){
		root=Merge(root,New(x));
	}
	void reverse(int l,int r){
		Split(root,l-1,rootX,rootZ);
		Split(rootZ,r-l+1,rootY,rootZ);
		q[rootY].lazy^=1;
		root=Merge(Merge(rootX,rootY),rootZ);
	}
	void to_ary(vector<int>&a){
		a.clear();
		Print(a,root);
	}
};
