template<class S>
struct MinXor{
	static_assert(std::is_integral_v<S>);
	multiset<S>a,b;
	void insert(S x){
		auto it=a.insert(x);
		auto nxt=next(it);
		if(it!=a.begin()){
			auto pre=prev(it);
			if(nxt!=a.end()) b.extract(*nxt^*pre);
			b.insert(*it^*pre);
		}
		if(nxt!=a.end()) b.insert(*nxt^*it);
	}
	void extract(S x){
		auto it=a.find(x);
		if(it==a.end()) return;
		auto nxt=next(it);
		if(it!=a.begin()){
			auto pre=prev(it);
			if(nxt!=a.end()) b.insert(*nxt^*pre);
			b.extract(*it^*pre);
		}
		if(nxt!=a.end()) b.extract(*nxt^*it);
		a.erase(it);
	}
	S min() const{
		if(b.empty()) return S(-1);
		return *b.begin();
	}
};
