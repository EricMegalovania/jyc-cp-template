#include<ext/pb_ds/assoc_container.hpp>
using __gnu_pbds::gp_hash_table;
using __gnu_pbds::null_type;

struct chash_int{
	static const uint64_t C=LL(4e18*acos(0))|71;
	LL operator()(LL x) const{
		return __builtin_bswap64(x*C);
	}
}
struct chash_vec{
	const size_t mg=0x9e3779b97f4a7c15;
	size_t operator()(const auto& v) const{
		size_t seed=mg;
		for(auto& x:v) {
			seed^=std::hash<LL>{}(x)+mg+(seed<<6)+(seed>>2);
		}
		return seed;
	}
};
// if multi test, change to 1<<4
gp_hash_table<int,null_type,chash_int>a({},{},{},{},{1<<16});
