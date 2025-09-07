// counter-clockwise
bool to_left_test(PDD a,PDD b,PDD c){
	return sign(cross(b-a,c-b))!=-1;
}
LD dis_point_poly(PDD a,vector<PDD>& b){
	const int n=b.size();
	bool ok=1;
	LD res=1e14;
	for(int j=0;j<n;++j){
		LD tmp=dis2seg(a,b[j],b[(j+1)%n]);
		res=fmin(res,tmp);
		if(!to_left_test(a,b[j],b[(j+1)%n])) ok=0;
	}
	if(ok) res=LD(0.0);
	return res;
}
