#include<ext/pb_ds/assoc_container.hpp>
using __gnu_pbds::gp_hash_table;
using __gnu_pbds::null_type;

using u64=uint64_t;
struct chash_int{
	static constexpr u64 C=u64(2e18*numbers::pi)|71;
	u64 operator()(LL x) const{ return __builtin_bswap64(x*C); }
};
struct chash_vec{ // mg 是黄金比例常数
	static constexpr u64 mg = 0x9e37'79b9'7f4a'7c15; //'
	u64 operator()(const auto& v) const{
		u64 seed=mg;
		for(auto x:v){ seed^=chash_int{}(x)+mg+(seed<<6)+(seed>>2); }
		return seed;
	}
};
// if multi test, change to 1<<4
gp_hash_table<int,null_type,chash_int>a({},{},{},{},{1<<16});
