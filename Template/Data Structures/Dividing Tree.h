// https://www.luogu.com.cn/articl/wzl5otpu
#define ls l,mid,o+1
#define rs mid+1,r,o+1
template<typename T>
struct DVT{ // dividing-tree
	vector<vector<T>>a;
	vector<vector<int>>tol; // val,to-lft
	vector<T>b; // b is sorted
	DVT(){}
	DVT(const vector<T>& v,int n){init(v,n);}
	void init(const vector<T>& v,int n){ // a1~an
		int m=__lg(n)+2;
		a.resize(m,vector<T>(n+1));
		tol.resize(m,vector<int>(n+1));
		b=v;
		sort(b.begin()+1,b.end());
		for(int i=1;i<=n;++i) a[0][i]=v[i];
		build(1,n);
	}
	void build(int l,int r,int o=0){
		if(l==r) return;
		int mid=l+r>>1;
		T key=b[mid];
		int eq=mid-l+1;
		for(int i=l;i<=r;i++){
			if(a[o][i]<key) --eq;
		}
		int tl=0,j=l-1,k=mid;
		for(int i=l;i<=r;i++){
			T nw=a[o][i];
			if(nw<key || (nw==key && eq)){
				if(nw==key) --eq;
				++tl;
				a[o+1][++j]=nw;
			}
			else{
				a[o+1][++k]=nw;
			}
			tol[o][i]=tl;	
		}
		build(ls);
		build(rs);
	}
	T query(int x,int y,int z,int l,int r,int o=0){
		// dvt in [l,r], query [x,y]'s z min
		if(l==r) return a[o][l];
		int mid=l+r>>1;
		int tl=0,del=tol[o][y];
		if(l!=x){
			tl=tol[o][x-1];
			del-=tl;
		}
		int nx,ny;	
		if(del>=z){
			nx=l+tl;
			ny=nx+del-1;
			return query(nx,ny,z,ls);
		}
		else{	
			nx=mid+1+x-tl-l;
			ny=nx+y-x-del;
			return query(nx,ny,z-del,rs);
		}
	}
};
#undef ls
#undef rs
