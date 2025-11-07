// 0-based-index, dx[i]=radius, which is [i to right]
// d0, i is center
// d1, between (i-1) and i is center
#define vi vector<int>
void manacher(auto&& s,vi& d0,vi& d1){
	const int& n=s.size();
#define WORK(X) d##X.assign(n,0); \
	for(int i=0,l=0,r=-1;i<n;++i){ \
	int k=(i>r)?0:min(d##X[l+r-i+X],r-i+1); \
	while(i-k-X>=0 && i+k<n && s[i-k-X]==s[i+k]) ++k; \
	d##X[i]=k--; if(i+k>r) l=i-k-X,r=i+k;}
	WORK(0); WORK(1);
#undef WORK
}
#undef vi
