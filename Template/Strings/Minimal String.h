int mininal_string(const string& s){
	const int n=s.size();
	int k=0,i=0,j=1;
	while(k<n && i<n && j<n){
		const char& ci=s[(i+k)%n];
		const char& cj=s[(j+k)%n];
		if(ci==cj) ++k;
		else{
			ci>cj ? i=i+k+1 : j=j+k+1;
			if(i==j) ++i;
			k=0;
		}
	}
	return min(i,j);
}
