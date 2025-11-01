#define sz(x) (int)((x).size())
template<typename T>
struct Med{
	multiset<T>a,b; // a:<=med, b:>=med
	LL sa,sb;
	//a.size()==b.size()+1 || a.size()==b.size()
	Med(){init();}
	void init(){
		clr(a),clr(b);
		sa=sb=0;
	}
	void rua(){
		if(sz(a)<sz(b)){
			auto it=b.begin();
			sa+=*it,sb-=*it;
			a.insert(*it);
			b.erase(it);
		}
		else if(sz(a)>sz(b)+1){
			auto it=--a.end();
			sa-=*it,sb+=*it;
			b.insert(*it);
			a.erase(it);
		}
	}
	void add(T x){
		if(b.empty() || x<=*b.begin()){
			a.insert(x);
			sa+=x;
		}
		else{
			b.insert(x);
			sb+=x;
		}
		rua();
	}
	void del(T x){
		auto it=a.find(x);
		if(it!=a.end()){
			a.erase(it);
			sa-=x;
		}
		else{
			b.extract(x);
			sb-=x;
		}
		rua();
	}
	T med_single() const{
		return *--a.end();
	}
	array<T,2> med_range() const{
		T l=med_single();
		if(sz(a)==sz(b)+1) return {l,l}; 
		return {l,*b.begin()};
	}
	LL cost() const{ // adjust all number to median's cost
		T mid=med_single();
		return (1ll*mid*a.size()-sa) + (sb-1ll*mid*b.size());
	}
};
#undef sz
