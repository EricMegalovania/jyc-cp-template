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

#define all(x) (x).begin(),(x).end()
#define allr(x) (x).rbegin(),(x).rend()

//快读
template<typename T>
inline T READ(){
	T x=0; bool f=0; char c=getchar();
	while(!isdigit(c)) f|=(c=='-'),c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return f?-x:x;
}
inline int read(){return READ<int>();}
inline LL readLL(){return READ<LL>();}
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int main(){
	
	return 0;
}
