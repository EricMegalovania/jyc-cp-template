bool cmpPDD(const PDD& A,const PDD& B){
	if(dcmp(A.y,B.y)==0) return dcmp(A.x,B.x)==-1;
	return dcmp(A.y,B.y)==-1;
}

// counter-clockwise
vector<PDD> Andrew(vector<PDD>& a){
	sort(all(a),cmpPDD);
	const int n=a.size();
	vector<PDD>b={a[0]};
#define sb (b.size())
	for(int i=1;i<n;++i){
		while(sb>1 && sign(area(b[sb-2],b[sb-1],a[i]))<=0)
			b.pop_back();
		b.push_back(a[i]);
	}
	const int m=sb;
	for(int i=n-2;i>=0;--i){
		while(sb>m && sign(area(b[sb-2],b[sb-1],a[i]))<=0)
			b.pop_back();
		b.push_back(a[i]);
	}
#undef sb
	b.pop_back();
	return b;
}
