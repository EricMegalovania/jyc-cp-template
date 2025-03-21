// mindeque template from 
// https://codeforces.com/blog/entry/122003
struct minstack {
	stack<pair<int, int>> st; //{T1, T2}
	int getmin() {return st.top().second;} //T2
	bool empty() {return st.empty();}
	int size() {return st.size();}
	void push(int x) { //x is T1
		int mn = x; //mn is T2
		if (!empty()) mn = min(mn, getmin());
		st.push({x, mn});
	}
	void pop() {st.pop();}
	int top() {return st.top().first;} //T1
	void swap(minstack &x) {st.swap(x.st);}
};
struct mindeque {
	minstack l, r, t;
	void reb() { //rebalance
		bool f = false;
		if (r.empty()) {f = true; l.swap(r);}
		int sz = r.size() / 2;
		while (sz--) {t.push(r.top()); r.pop();}
		while (!r.empty()) {l.push(r.top()); r.pop();}
		while (!t.empty()) {r.push(t.top()); t.pop();}
		if (f) l.swap(r);
	}
	int getmin() { //T2
		if (l.empty()) return r.getmin();
		if (r.empty()) return l.getmin();
		return min(l.getmin(), r.getmin());
	}
	bool empty() {return l.empty() && r.empty();}
	int size() {return l.size() + r.size();}
	void push_front(int x) {l.push(x);} //arg is T1
	void push_back(int x) {r.push(x);} //arg is T1
	void pop_front() {if (l.empty()) reb(); l.pop();}
	void pop_back() {if (r.empty()) reb(); r.pop();}
	int front() {if (l.empty()) reb(); return l.top();} //T1
	int back() {if (r.empty()) reb(); return r.top();} //T1
	void swap(mindeque &x) {l.swap(x.l); r.swap(x.r);}
};
