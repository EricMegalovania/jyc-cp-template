void build_tree(string& s,auto&& e,auto&& id){
	const int n=(int)(s.size())/2;
	s.insert(0,"("); s+=")";
	e.assign(n+1,{});
	id.assign(s.size(),-1);
	int tot=0;
	stack<int>stk;
	for(int i=0;i<(int)s.size();++i){
		if(s[i]=='('){
			if(stk.size()){
				e[stk.top()].emplace_back(tot);
			}
			stk.push(tot);
			id[i]=tot++;
		}
		else{
			id[i]=stk.top();
			stk.pop();
		}
	}
}
