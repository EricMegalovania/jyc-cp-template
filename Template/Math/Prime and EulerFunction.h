bitset<N>notP; int phi[N],mn_p[N];
vector<int>prime;
void init_prime(const int& n=N){ // init [1,n-1]
	phi[1]=mn_p[1]=notP[1]=1;
	for(int i=2;i<n;i++){
		if(!notP[i]){
			prime.push_back(mn_p[i]=i);
			phi[i]=i-1;
		}
		for(const int& p:prime){
			if(i>(n-1)/p) break;
			notP[i*p]=1,mn_p[i*p]=p;
			if(i%p==0){
				phi[i*p]=phi[i]*p;
				break;
			}
			phi[i*p]=phi[i]*(p-1);
		}
	}
}
