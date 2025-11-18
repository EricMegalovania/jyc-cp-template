#include<ext/pb_ds/priority_queue.hpp>
using _pairing=__gnu_pbds::pairing_heap_tag;
using _binary=__gnu_pbds::binary_heap_tag;
// user defined: _pairing, else: _binary
template<class S,class Cmp=std::less<S>,class Tag=_pairing>
using heap=__gnu_pbds::priority_queue<S,Cmp,Tag>;
