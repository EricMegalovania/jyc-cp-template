#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
namespace __gnu_rb_tree{
	using namespace __gnu_pbds;
	template<class Key,class Mapped=null_type,class Cmp=std::less<Key>>
	using rb_tree=tree<Key,Mapped,Cmp,rb_tree_tag,tree_order_statistics_node_update>;
}
using __gnu_rb_tree::rb_tree;

namespace __multi_rb_tree{
	using namespace __gnu_pbds;
	template<class T,class Cmp=std::less<T>>
	struct Wrapper{
		bool operator()(const std::pair<T,int>& a,const std::pair<T,int>& b) const{
			if(Cmp{}(a.first,b.first)) return 1; // a.T < b.T
			if(Cmp{}(b.first,a.first)) return 0; // b.T < a.T
			return a.second<b.second; // a.T == b.T
		}
	};
	template<class Key,class Cmp=std::less<Key>>
	class multiset_rb_tree{
		rb_tree<std::pair<Key,int>,null_type,Wrapper<Key,Cmp>>rbt;
		int count;
		using S=std::pair<Key,bool>;
		static consteval S e(){ return S{Key{},0}; }
		S _ret(auto&& it){
			if(it!=rbt.end()) return {it->first,1};
			else return e();
		}
	public:
		multiset_rb_tree():count(0){}
		void insert(const Key& x){
			rbt.insert({x,count++});
		}
		void erase(const Key& x){
			auto it=rbt.lower_bound({x,0});
			while(it!=rbt.end() && it->first==x){
				it=rbt.erase(it);
			}
		}
		void extract(const Key& x){
			auto it=rbt.lower_bound({x,0});
			if(it!=rbt.end() && it->first==x){
				rbt.erase(it);
			}
		}
		std::size_t order_of_key(const Key& x){
			return rbt.order_of_key({x,0});
		}
		S find_by_order(int x){ // 0-index-based
			return _ret(rbt.find_by_order(x));
		}
		S ge(const Key& x){ // greater equal, >=x
			return _ret(rbt.lower_bound({x,0}));
		}
		S lt(const Key& x){ // less than, <x
			if(empty()) return e();
			auto it=rbt.lower_bound({x,0});
			if(it==rbt.begin()) return e();
			else return _ret(--it);
		}
		S gt(const Key& x){ // greater than, >x
			return _ret(rbt.upper_bound({x,INT_MAX}));
		}
		S le(const Key& x){ // less equal, <=x
			if(empty()) return e();
			auto it=rbt.upper_bound({x,INT_MAX});
			if(it==rbt.begin()) return e();
			else return _ret(--it);
		}
		bool find(const Key& x) const{ return rbt.find(x)!=rbt.end(); }
		bool empty() const{ return rbt.empty(); }
		std::size_t size() const{ return rbt.size(); }
	};
}
using __multi_rb_tree::multiset_rb_tree;
