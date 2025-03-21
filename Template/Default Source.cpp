#include<bits/stdc++.h>
using namespace std;

//#define ONLINE
#ifndef ONLINE
char DEBUG_BUFFER[1000];
#define debug(...) {sprintf(DEBUG_BUFFER,##__VA_ARGS__);cerr<<DEBUG_BUFFER;}
#else
#define debug(...) ;
#endif

using LL=long long;
using PII=pair<int,int>;

#define all(x) (x).begin(),(x).end()
#define allr(x) (x).rbegin(),(x).rend()

#define FAST_IO {ios::sync_with_stdio(false);cin.tie(nullptr);}
inline int read(){static int x; cin>>x; return x;}
inline LL readLL(){static LL x; cin>>x; return x;}
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

int main(){
	FAST_IO;
	return 0;
}
