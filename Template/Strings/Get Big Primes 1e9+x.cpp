#include<bits/stdc++.h>
using namespace std;

int main(){
	const int N=500;
	vector<int>a;
	auto deal=[&](const int& x)->void{
		for(int i=2;i*i<=x;i++){
			if(x%i==0) return;
		}
		a.push_back(x-1e9);
	};
	for(int i=1;a.size()<N;i++){
		deal(1e9+i);
	}
	printf("const int TABLE_SIZE=%d;\n",N);
	printf("const int table[TABLE_SIZE]={%d",a[0]);
	for(int i=1;i<N;i++) printf(",%d",a[i]);
	printf("};");
	return 0;
}
