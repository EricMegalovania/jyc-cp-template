// mindeque template from 
// https://codeforces.com/blog/entry/122003
template<class S,auto op>struct minstack{
	stack<pair<S,S>>st; // {T1, T2}
	S getmin(){ return st.top().second; } // T2
	bool empty(){ return st.empty(); }
	int size(){ return (int)st.size(); }
	void push(S x){ // x is T1
		S mn=x; // mn is T2
		if(!empty()) mn=op(mn,getmin());
		st.emplace(x,mn);
	}
	void pop(){ st.pop(); }
	S top(){ return st.top().first; } // T1
	void swap(minstack &x){ st.swap(x.st); }
};
template<class S,auto op>struct mindeque{
	minstack<S,op>l,r,t;
	void reb(){ // rebalance
		bool f=0;
		if(r.empty()){ f=1; l.swap(r); }
		int sz=(int)(r.size())/2;
		while(sz--){ t.push(r.top()); r.pop(); }
		while(!r.empty()){ l.push(r.top()); r.pop(); }
		while(!t.empty()){ r.push(t.top()); t.pop(); }
		if(f) l.swap(r);
	}
	S getmin(){ // T2
		if(l.empty()) return r.getmin();
		if(r.empty()) return l.getmin();
		return op(l.getmin(), r.getmin());
	}
	bool empty(){ return l.empty() && r.empty(); }
	int size(){ return (int)l.size()+(int)r.size(); }
	void push_front(S x){ l.push(x); } // arg is T1
	void push_back(S x){ r.push(x); } // arg is T1
	void pop_front(){ if(l.empty()) reb(); l.pop(); }
	void pop_back(){ if(r.empty()) reb(); r.pop(); }
	S front(){ if(l.empty()) reb(); return l.top(); } // T1
	S back(){ if(r.empty()) reb(); return r.top(); } // T1
	void swap(mindeque &x){ l.swap(x.l); r.swap(x.r); }
};
