using u128=__uint128_t;
namespace POPCNT{
	char tab[1<<16];
	inline void init(){
		for(int x=1;x<(1<<16);x++){
			tab[x]=tab[x&(x-1)]+1;
		}
	}
	inline int u128_count(const u128& x){
		return tab[x&0xffff]+
		tab[(x>>16)&0xffff]+
		tab[(x>>32)&0xffff]+
		tab[(x>>48)&0xffff]+
		tab[(x>>64)&0xffff]+
		tab[(x>>80)&0xffff]+
		tab[(x>>96)&0xffff]+
		tab[(x>>112)&0xffff];
	}
}
using POPCNT::u128_count;

template<int N_>
struct Bitset{
	static const int N=(N_-1)/128+1,back_siz=N_-(N-1)*128;
	static const u128 o=1,set_last=(o<<back_siz-1)-1+(o<<back_siz-1);
	u128 a[N];
	inline void reset(){
		memset(a,0,sizeof(a));
	}
	inline void set(){
		memset(a,0xff,sizeof(a));
		a[N-1]=set_last;
	}
	inline Bitset(const bool& _=0){
		_?set():reset();
	}
	inline void flip(int x){
		a[x>>7]^=o<<(x&127);
	}
	inline void reset(int x){
		a[x>>7]&=~(o<<(x&127));
	}
	inline void set(int x){
		a[x>>7]|=o<<(x&127);
	}
	inline int test(int x){
		return (a[x>>7]>>(x&127))&1;
	}
	inline Bitset operator ~() const{
		Bitset ret(N);
		for(int i=0;i<N;i++){
			ret.a[i]=~a[i];
		}
		return ret;
	}
	inline Bitset operator &(const Bitset &b) const{
		Bitset ret(N);
		for(int i=0;i<N;i++){
			ret.a[i]=a[i]&b.a[i];
		}
		return ret;
	}
	inline Bitset operator |(const Bitset &b) const{
		Bitset ret;
		for(int i=0;i<N;i++){
			ret.a[i]=a[i]|b.a[i];
		}
		return ret;
	}
	inline Bitset operator ^(const Bitset &b) const{
		Bitset ret;
		for(int i=0;i<N;i++){
			ret.a[i]=a[i]^b.a[i];
		}
		return ret;
	}
	inline Bitset operator <<(const int& t) const{
		Bitset ret;
		u128 last=0;
		int high=t>>7,low=t&127;
		for(int i=0;i+high<N;i++){
			ret.a[i+high]=last|(a[i]<<low);
			if(low) last=a[i]>>(128-low);
		}
		return ret;
	}
	inline Bitset operator >>(const int& t) const{
		Bitset ret;
		u128 last=0;
		int high=t>>7,low=t&127;
		for(int i=N-1;i>=high;i--){
			ret.a[i-high]=last|(a[i]>>low);
			if(low) last=a[i]<<(128-low);
		}
		return ret;
	}
	inline string str() const{
		string s="";
		for(int j=back_siz-1;j>=0;j--){
			s.push_back('0'+(a[N-1]>>j&1));
		}
		for(int i=N-2;i>=0;i--){
			for(int j=127;j>=0;j--){
				s.push_back('0'+(a[i]>>j&1));
			}
		}
		return s;
	}
	inline int count() const{
		int ret=0;
		for(int i=0;i<N;i++){
			ret+=u128_count(a[i]);
		}
		return ret;
	}
};

POPCNT::init();
