#include<bits/stdc++.h>
using namespace std;

//#define ONLINE
#ifndef ONLINE
#define debug(...) fprintf(stderr,##__VA_ARGS__)
#else
#define debug(...) ;
#endif

using LL=long long;
using PII=pair<int,int>;

//double关键字比大小
#define eps (1e-8)
inline int sign(const double& x){
	if(fabs(x)<eps) return 0;
	return x>0.0?1:-1;
}
inline int dcmp(const double& x,const double& y){
	return sign(x-y);
}

//快读
template<typename T>
inline T READ(){
	T x=0; bool f=0; char c=getchar();
	while(c<'0' || c>'9') f|=(c=='-'),c=getchar();
	while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return f?-x:x;
}
inline int read(){return READ<int>();}
inline LL readLL(){return READ<LL>();}
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

const int mod=998244353;
int main(){
	
	return 0;
}
