template<typename T> // Cartesian-Tree, index: 1~n
int CT(const vector<T>& a,const int& n,vector<int>& ls,vector<int>& rs){
	ls.assign(n+1,0),rs.assign(n+1,0);
	vector<int>stk(n+1);
	for(int i=1,top=0,k=0;i<=n;i++,k=top){
		while(k && a[stk[k]]>a[i]) k--;
		if(k) rs[stk[k]]=i;
		if(k<top) ls[i]=stk[k+1];
		stk[top=++k]=i;
	}
	return stk[1]; // root
}
