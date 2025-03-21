vector<PDD> Andrew(vector<PDD>& a){
	sort(a.begin(),a.end(),[](const PDD& A,const PDD& B){
		if(dcmp(A.y,B.y)==0) return dcmp(A.x,B.x)==-1;
		return dcmp(A.y,B.y)==-1;
	});
	vector<PDD>up={a[0]};
	for(int i=1;i<a.size();i++){
		while(up.size()>=2 && sign(area(up[up.size()-2],up.back(),a[i]))>=0)
			up.pop_back();
		up.push_back(a[i]);
	}
	vector<PDD>down={up.back()};
	for(int i=a.size()-1;i>=0;i--){
		while(down.size()>=2 && sign(area(down[down.size()-2],down.back(),a[i]))>=0)
			down.pop_back();
		down.push_back(a[i]);
	}
	reverse(all(down));
	down.pop_back();
	up.erase(up.begin());
	down.insert(down.end(),all(up));
	return down;
}
