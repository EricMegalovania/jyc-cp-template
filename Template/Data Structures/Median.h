#define sz(x) (int)((x).size())
template<typename T>
struct Med{
	multiset<T>a,b; // a:<=med, b:>=med
	//a.size()==b.size()+1 || a.size()==b.size()
	void init(){
		a.clear();
		b.clear();
	}
	void rua(){
		if(sz(a)<sz(b)){
			auto it=b.begin();
			a.insert(*it);
			b.erase(it);
		}
		else if(sz(a)>sz(b)+1){
			auto it=--a.end();
			b.insert(*it);
			a.erase(it);
		}
	}
	void add(T x){
		if(b.empty() || x<=*b.begin()) a.insert(x);
		else b.insert(x);
		rua();
	}
	void del(T x){
		auto it=a.find(x);
		if(it!=a.end()) a.erase(it);
		else b.extract(x);
		rua();
	}
	ai2 med(){
		T l=*--a.end();
		if(sz(a)==sz(b)+1) return {l,l}; 
		return {l,*b.begin()};
	}
};
#undef sz
