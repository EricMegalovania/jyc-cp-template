struct DSU{
	vector<int>fa,siz;
	DSU(){}
	DSU(int n){
		init(n);
	}
	void init(int n){
		fa.resize(n);
		iota(fa.begin(),fa.end(),0);
		siz.assign(n,1);
	}
	int get(int x){
		while(x!=fa[x]){
			x=fa[x]=fa[fa[x]];
		}
		return x;
	}
	bool same(int x,int y){
		return get(x)==get(y);
	}
	bool merge(int x,int y){
		x=get(x),y=get(y);
		if(x==y) return 0;
		if(siz[y]>siz[x]) swap(x,y);
		siz[x]+=siz[y],fa[y]=x;
		return 1;
	}
	int size(int x){
		return siz[get(x)];
	}
};
