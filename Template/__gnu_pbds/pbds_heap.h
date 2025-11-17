#include<ext/pb_ds/priority_queue.hpp>
namespace __meg_heap{
	using namespace __gnu_pbds;
	// user defined: pairing_, else: binary_
	template<class S,class Cmp=std::less<S>,class Tag=binary_heap_tag>
	using heap=priority_queue<S,Cmp,Tag>;
}
using __meg_heap::heap;
