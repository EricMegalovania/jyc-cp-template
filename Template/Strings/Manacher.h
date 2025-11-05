// 0-based-index, dx[i]=radius, which is [i to right]
// d1, i is center
// d2, between (i-1) and i is center
void manacher(auto&& s,auto&& d1,auto&& d2){
	const int& n=s.size();
	d1.assign(n,0);
	for(int i=0,l=0,r=-1;i<n;++i){
		int k=(i>r)?1:min(d1[l+r-i],r-i+1);
		while(i-k>=0 && i+k<n && s[i-k]==s[i+k]){
			++k;
		}
		d1[i]=k--;
		if(i+k>r){
			l=i-k,r=i+k;
		}
	}
	d2.assign(n,0);
	for(int i=0,l=0,r=-1;i<n;++i){
		int k=(i>r)?0:min(d2[l+r-i+1],r-i+1);
		while(i-k-1>=0 && i+k<n && s[i-k-1]==s[i+k]){
			++k;
		}
		d2[i]=k--;
		if(i+k>r){
			l=i-k-1,r=i+k;
		}
	}
}
