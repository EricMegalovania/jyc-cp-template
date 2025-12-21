// counter-clockwise
// this calc a+(-b), dis of poly a, b
// cmpPDD from Andrew.h
vector<PDD> Minkowski(vector<PDD> a, vector<PDD> b) {
//	a=Andrew(a);
	for(auto& [x,y]:b) x=-x,y=-y;
//	b=Andrew(b);
	rotate(b.begin(),min_element(all(b),cmpPDD),b.end());
	vector<PDD>c{a[0]+b[0]};
	const int n=(int)a.size();
	const int m=(int)b.size();
	PDD al=a[0]-a[n-1],bl=b[0]-b[m-1];
	for(int i=0;i+1<n;++i) a[i]=a[i+1]-a[i];
	for(int i=0;i+1<m;++i) b[i]=b[i+1]-b[i];
	a[n-1]=al,b[m-1]=bl;
	c.resize(n+m+1);
	merge(all(a),all(b),c.begin()+1,
		[&](const PDD&x, const PDD &y){return sign(cross(x,y))==1;});
	c.pop_back();
	for(int i=1;i<(int)c.size();++i) c[i]=c[i]+c[i-1];
	return c;
}