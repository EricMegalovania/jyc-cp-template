class DSU{
private:
	vector<int>fa,siz;
public:
	DSU(){}
	DSU(int n){
		init(n);
	}
	void init(int n){
		fa.resize(n);
		iota(fa.begin(),fa.end(),0);
		siz.assign(n,1);
	}
	int find(int x){
		while(x!=fa[x]){
			x=fa[x]=fa[fa[x]];
		}
		return x;
	}
	bool same(int x,int y){
		return find(x)==find(y);
	}
	bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y) return 0;
		if(siz[y]>siz[x]) swap(x,y);
		siz[x]+=siz[y],fa[y]=x;
		return 1;
	}
	int size(int x){
		return siz[find(x)];
	}
};
