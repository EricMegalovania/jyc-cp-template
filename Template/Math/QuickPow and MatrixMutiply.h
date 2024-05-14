#include<bits/stdc++.h>
using namespace std;

using LL=long long;

const int mod=1e9+7;
LL ksm(LL a,LL b){
	a%=mod; LL ret=1;
	while(b){
		if(b&1) ret=ret*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ret;
}

void mul(const vector<vector<LL>>& a,vector<LL>& f,int n){//f=a*f
	vector<LL>b(n,0);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			b[i]=(b[i]+a[i][j]*f[j]%mod)%mod;
		}
	}
	swap(f,b);
}
void self_mul(vector<vector<LL>>& a,int n){//a=a*a
	vector b(n,vector<LL>(n,0));
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				b[i][j]=(b[i][j]+a[i][k]*a[k][j]%mod)%mod;
			}
		}
	}
	swap(a,b);
}
