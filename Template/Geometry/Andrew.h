void Andrew(vector<PDD>& a,vector<PDD>& up,vector<PDD>& down){
	sort(a.begin(),a.end(),[](const PDD& A,const PDD& B){
		if(dcmp(A.y,B.y)==0) return dcmp(A.x,B.x)==-1;
		return dcmp(A.y,B.y)==-1;
	});
	up={a[0]};
	for(int i=1;i<a.size();i++){
		while(up.size()>=2 && sign(area(up[up.size()-2],up.back(),a[i]))>=0)
			up.pop_back();
		up.push_back(a[i]);
	}
	down={up.back()};
	for(int i=a.size()-1;i>=0;i--){
		while(down.size()>=2 && sign(area(down[down.size()-2],down.back(),a[i]))>=0)
			down.pop_back();
		down.push_back(a[i]);
	}
}
