#define __AVX__ 1
#define __AVX2__ 1
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,fma,popcnt")
#include<immintrin.h>

#define ONLINE
#ifndef ONLINE
char DEBUG_BUFFER[1000];
#define debug(...) {sprintf(DEBUG_BUFFER,##__VA_ARGS__);\
cerr<<"\033[1;36m"<<DEBUG_BUFFER<<"\033[0;2m"<<"\033[0m";}
#else
#define debug(...) ;
#endif
#define __JYC_CP
namespace avx256_bitset{
	using vec=__m256i;
	using u32=unsigned int;
	using u64=unsigned long long;
	using cup=const u32*; //const-u32-pointer
	const u32 o=1,inf=0xffffffff;
#define v32(x) _mm256_##x
#define B Bitset<N>
#define vec_zero (v32(set1_epi32)(0))
#define vec_one (v32(set1_epi32)(inf))
#define load(x) (v32(load_si256)((vec*)(x)))
#define loadu(x) (v32(loadu_si256)((vec*)(x)))
	template<const int N>
	class Bitset{
	private:
		static_assert(N%256==0);
		static const int T=(N-1)/32+1,T2=((N-1)/256+1)<<3,back_siz=N-32*(T-1);
		static_assert(back_siz>=0 && back_siz<=32);
		static const u32 set_last=(o<<back_siz-1)-1+(o<<back_siz-1);
		alignas(32) u32 a[T2]={};
		inline void revise(){
			a[T-1]&=set_last;
			for(int i=T;i<T2;++i) a[i]=0;
		}
	public:
		Bitset(){}
		inline void reset(){
			static const vec all_zero=vec_zero;
			cup p=a,pend=a+T2;
			for(;p!=pend;p+=8){
				v32(store_si256)((vec*)p,all_zero);
			}
		}
		inline void set(){
			static const vec all_one=vec_one;
			cup p=a,pend=a+T2;
			for(;p!=pend;p+=8){
				v32(store_si256)((vec*)p,all_one);
			}
			revise();
		}
		inline void reset(const int& x){
			a[x>>5]&=~(o<<x&31);
			if((x>>5)==T-1) a[T-1]&=set_last;
		}
		inline void set(const int& x){
			a[x>>5]|=o<<(x&31);
		}
		inline void flip(const int& x){
			a[x>>5]^=o<<(x&31);
		}
		inline int test(int x){
			return (a[x>>5]>>(x&31))&1;
		}
		inline bool operator [](int x) const{
			return (a[x>>5]>>(x&31))&1;
		}
		inline bool none() const{
			cup p=a,pend=a+T2;
			for(;p!=pend;p+=8){
				const vec& v=load(p);
				if(!v32(testz_si256)(v,v)) return 0;
			}
			return 1;
		}
		inline bool any() const{
			return !none();
		}
		inline int _Find_first() const{
			for(int i=0;i<T2;i+=8){
				const vec& v=load(&a[i]);
				if(v32(testz_si256)(v,v)) continue;
				for(int j=i;j<i+8;j++) if(a[j]){
					return j*32+__builtin_ctz(a[j]);
				}
			}
			return N;
		}
		inline int _Find_next(const int& pos) const{
			if((pos&31)!=31){
				int i=pos/32,j=(pos+1)&31,nw=pos+1;
				for(;j<32;++j,++nw){
					if(a[i]>>j&1) return nw;
				}
			}
			int i=pos/32+1;
			for(;i%8;++i) if(a[i]){
				return i*32+__builtin_ctz(a[i]);
			}
			for(;i<T2;i+=8){
				const vec& v=load(&a[i]);
				if(v32(testz_si256)(v,v)) continue;
				for(int j=i;j<i+8;j++) if(a[j]){
					return j*32+__builtin_ctz(a[j]);
				}
			}
			return N;
		}
		inline int count() const{
			int ans=0;
			for(int i=0;i<T2/2;++i){
				ans+=__builtin_popcountll( ((u64*)(a)) [i]);
			}
			return ans;
			//needs to support avx512
			//flags: AVX512VPOPCNTDQ + AVX512VL
			/*
			int ans[8]={};
			vec res=vec_zero,tmp;
			cup p=a,pend=a+T2;
			for(;p!=pend;p+=8){
			tmp=v32(popcnt_epi32)(load(p));
			res=v32(add_epi32)(res,tmp);
			}
			v32(store_si256)((vec*)ans,res);
			return accumulate(ans,ans+8,0);
			*/
		}
		inline B& operator =(const B& b){
			u32* p=a;
			cup pend=a+T2,p2=b.a;
			for(;p!=pend;p+=8,p2+=8){
				v32(store_si256)((vec*)p,load(p2));
			}
			return *this;
		}
		inline B operator ~() const{
			static const __m256i all_one=vec_one;
			B ans; cup p=a,pend=a+T2;
			u32* pans=ans.a;
			for(;p!=pend;p+=8,pans+=8){
				auto v=v32(load_si256)((vec*)p);
				v=v32(andnot_si256)(v,all_one);
				v32(store_si256)((vec*)pans,v);
			}
			revise();
			return ans;
		}
#define OP(b,op) \
		B ans; cup p=a,pend=a+T2,p2=b.a;\
		u32* pans=ans.a;\
		for(;p!=pend;p+=8,p2+=8,pans+=8){\
		const vec& tmp=v32(op##_si256)(load(p),load(p2));\
		v32(store_si256)((vec*)pans,tmp);\
		}return ans
		inline B operator &(const B& b) const{
			OP(b,and);
		}
		inline B operator |(const B& b) const{
			OP(b,or);
		}
		inline B operator ^(const B& b) const{
			OP(b,xor);
		}
#undef OP
#define OP(b,op) \
		cup p=a,pend=a+T2,p2=b.a;\
		for(;p!=pend;p+=8,p2+=8){\
		const vec& tmp=v32(op##_si256)(load(p),load(p2));\
		v32(store_si256)((vec*)p,tmp);\
		}return *this
		inline B& operator &=(const B& b){
			OP(b,and);
		}
		inline B& operator |=(const B& b){
			OP(b,or);
		}
		inline B& operator ^=(const B& b){
			OP(b,xor);
		}
#undef OP
		inline B operator <<(const int& t) const{
			B ans;
			if(t>=N) return ans;
			const int div=t/32,rem=t%32;
			cup p=a+T2-8;
			u32* pans=ans.a+T2-8;
			if(rem){
				for(;p-div-1>=a;p-=8,pans-=8){
					vec v1=v32(slli_epi32)(loadu(p-div),rem);
					vec v2=v32(srli_epi32)(loadu(p-div-1),32-rem);
					v32(store_si256)((vec*)pans,v32(or_si256)(v1,v2));
				}
			}
			else{
				for(;p-div-1>=a;p-=8,pans-=8){
					v32(store_si256)((vec*)pans,loadu(p-div));
				}
			}
			p+=7,pans+=7;
			for(;p-div-1>=a;--p,--pans){
				(*pans)=(*(p-div))<<rem;
				if(rem) (*pans)|=(*(p-div-1))>>(32-rem);
			}
			(*pans)=a[0]<<rem;
			ans.revise();
			return ans;
		}
		inline B& operator <<=(const int& t){
			return (*this)=(*this)<<t;
		}
		inline B operator >>(const int& t) const{
			B ans;
			if(t>=N) return ans;
			const int div=t/32,rem=t%32;
			cup p=a;
			u32* pans=ans.a;
			if(rem){
				for(;p+div+1<=a+T2-8;p+=8,pans+=8){
					vec v1=v32(srli_epi32)(loadu(p+div),rem);
					vec v2=v32(slli_epi32)(loadu(p+div+1),32-rem);
					v32(store_si256)((vec*)pans,v32(or_si256)(v1,v2));
				}
			}
			else{
				for(;p+div+1<=a+T2-8;p+=8,pans+=8){
					v32(store_si256)((vec*)pans,loadu(p+div));
				}
			}
			p-=7,pans-=7;
			for(;p+div+1<=a+T2-8;++p,++pans){
				(*pans)=(*(p+div))>>rem;
				if(rem) (*pans)|=(*(p+div+1))<<(32-rem);
			}
			(*pans)=a[T2-1]>>rem;
			ans.revise();
			return ans;
		}
		inline B& operator >>=(const int& t){
			return (*this)=(*this)>>t;
		}
//the following parts are for competitive programming
#ifdef __JYC_CP
#define OP(x,y,z,op) \
		cup p=x.a,pend=x.a+T2,p2=y.a;\
		u32* pans=z.a;\
		for(;p!=pend;p+=8,p2+=8,pans+=8){\
		const vec& tmp=v32(op##_si256)(load(p),load(p2));\
		v32(store_si256)((vec*)pans,tmp);}
		inline static void And(const B& x,const B& y,B& z){
			OP(x,y,z,and);
		}
		inline static void Or(const B& x,const B& y,B& z){
			OP(x,y,z,or);
		}
		inline static void Xor(const B& x,const B& y,B& z){
			OP(x,y,z,xor);
		}
#undef OP
		inline static void Lsh(const B& x,const int& t,B& ans){
			if(t>=N){
				ans.reset();
				return;
			}
			const int div=t/32,rem=t%32;
			cup p=x.a+T2-8;
			u32* pans=ans.a+T2-8;
			if(rem){
				for(;p-div-1>=x.a;p-=8,pans-=8){
					vec v1=v32(slli_epi32)(loadu(p-div),rem);
					vec v2=v32(srli_epi32)(loadu(p-div-1),32-rem);
					v32(store_si256)((vec*)pans,v32(or_si256)(v1,v2));
				}
			}
			else{
				for(;p-div-1>=x.a;p-=8,pans-=8){
					v32(store_si256)((vec*)pans,loadu(p-div));
				}
			}
			p+=7,pans+=7;
			for(;p-div-1>=x.a;--p,--pans){
				(*pans)=(*(p-div))<<rem;
				if(rem) (*pans)|=(*(p-div-1))>>(32-rem);
			}
			(*pans)=x.a[0]<<rem;
			ans.revise();
		}
		inline static void Rsh(const B& x,const int& t,B& ans){
			if(t>=N){
				ans.reset();
				return;
			}
			const int div=t/32,rem=t%32;
			cup p=x.a;
			u32* pans=ans.a;
			if(rem){
				for(;p+div+1<=x.a+T2-8;p+=8,pans+=8){
					vec v1=v32(srli_epi32)(loadu(p+div),rem);
					vec v2=v32(slli_epi32)(loadu(p+div+1),32-rem);
					v32(store_si256)((vec*)pans,v32(or_si256)(v1,v2));
				}
			}
			else{
				for(;p+div+1<=x.a+T2-8;p+=8,pans+=8){
					v32(store_si256)((vec*)pans,loadu(p+div));
				}
			}
			p-=7,pans-=7;
			for(;p+div+1<=x.a+T2-8;++p,++pans){
				(*pans)=(*(p+div))>>rem;
				if(rem) (*pans)|=(*(p+div+1))<<(32-rem);
			}
			(*pans)=x.a[T2-1]>>rem;
			ans.revise();
		}
		inline int count(int n) const{
			int ans=0;
			for(int i=0;i<n+63;i+=64){
				ans+=__builtin_popcountll(*((u64*)(a+i/32) ));
			}
			return ans;
		}
#endif
		string str() const{
			string s="";
			for(int i=N-1;i>=0;--i){
				s.push_back('0'+(int)operator[](i));
			}
			return s;
		}
		void output() const{
			debug("%s\n",this->str().data());
		}
	};
}
#undef B

//N%256==0
using B=avx256_bitset::Bitset<N>;
