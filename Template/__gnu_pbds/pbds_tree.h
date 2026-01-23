#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
namespace __gnu_rb_tree{
	using namespace __gnu_pbds;
	template<class Key,class Mapped=null_type,class Cmp=std::less<Key>>
	using rb_tree=tree<Key,Mapped,Cmp,rb_tree_tag,tree_order_statistics_node_update>;
}
using __gnu_rb_tree::rb_tree;

#define x first
#define y second
#define lo lower_bound
#define up upper_bound
namespace __multi_rb_tree{
	using namespace __gnu_pbds;
	template<class T,class Cmp=std::less<T>>
	struct Wrapper{
		using S=std::pair<T,int>;
		bool operator()(const S& a,const S& b) const{
			if(Cmp{}(a.x,b.x)) return 1; // a.T < b.T
			if(Cmp{}(b.x,a.x)) return 0; // b.T < a.T
			return a.y<b.y; // a.T == b.T
		}
	};
	template<class T,class Cmp=std::less<T>>
	class multiset_rb_tree{
		rb_tree<std::pair<T,int>,null_type,Wrapper<T,Cmp>>a;
		int count;
		using S=std::pair<T,bool>;
		static consteval S e(){ return S{T{},0}; }
		S _ret(auto&& it){ return (it!=a.end()) ? S{it->x,1} : e(); }
	public:
		multiset_rb_tree():count(0){}
		void insert(const T& x){ a.insert({x,count++}); }
		void erase(const T& x){
			auto it=a.lo({x,0});
			while(it!=a.end() && it->x==x) it=a.erase(it);
		}
		void extract(const T& x){
			auto it=a.lo({x,0});
			if(it!=a.end() && it->x==x) a.erase(it);
		}
		std::size_t order_of_key(const T& x){ // # keys strictly < x
			return a.order_of_key({x,0});
		}
		S find_by_order(int x){ // 0-index-based
			return _ret(a.find_by_order(x));
		}
		S ge(const T& x){ // greater equal, >=x
			return _ret(a.lo({x,0}));
		}
		S lt(const T& x){ // less than, <x
			if(empty()) return e();
			auto it=a.lo({x,0});
			if(it==a.begin()) return e();
			else return _ret(--it);
		}
		S gt(const T& x){ // greater than, >x
			return _ret(a.up({x,INT_MAX}));
		}
		S le(const T& x){ // less equal, <=x
			if(empty()) return e();
			auto it=a.up({x,INT_MAX});
			if(it==a.begin()) return e();
			else return _ret(--it);
		}
		bool find(const T& x) const{ return a.find(x)!=a.end(); }
		bool empty() const{ return a.empty(); }
		std::size_t size() const{ return a.size(); }
	};
}
#undef x
#undef y
#undef lo
#undef up
using __multi_rb_tree::multiset_rb_tree;
