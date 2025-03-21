struct DSU{
	vector<int>fa,siz;
	vector<LL>d;
	DSU(){}
	DSU(int n){
		init(n);
	}
	void init(int n){
		fa.resize(n);
		iota(fa.begin(),fa.end(),0);
		siz.assign(n,1);
		d.assign(n,0);
	}
	int get(int x){
		if(x==fa[x]) return x;
		int root=get(fa[x]);
		d[x]^=d[fa[x]];
		return fa[x]=root;
	}
	bool same(int x,int y){
		return get(x)==get(y);
	}
	bool merge(int x,int y,LL z){
		get(x),get(y);
		LL dx=d[x],dy=d[y];
		x=fa[x],y=fa[y];
		if(x==y) return 0;
		if(siz[y]>siz[x]) swap(x,y);
		siz[x]+=siz[y],fa[y]=x;
		d[y]=dx^dy^z;
		return 1;
	}
	int size(int x){
		return siz[get(x)];
	}
};
