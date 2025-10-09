/*
f(n)=\sum_{d|n} g(d)
- g(n)=\sum_{d|n} mu(d)*f(n/d)
f(n)=\sum_{n|d} g(d)
- g(n)=\sum_{n|d} mu(d/n)f(d)
*/
bitset<N>notP;
int mu[N],mn_p[N];
int d[N],num[N];
vector<int>prime;
void init_prime(const int& n=N){//init [1,n-1]
	mu[1]=mn_p[1]=notP[1]=1;
	d[1]=1;
	for(int i=2;i<n;i++){
		if(!notP[i]){
			prime.push_back(mn_p[i]=i);
			mu[i]=-1;
			d[i]=2,num[i]=1;
		}
		for(const int& p:prime){
			if(i>(n-1)/p) break;
			int j=i*p;
			notP[j]=1,mn_p[j]=p;
			if(i%p==0){
				mu[j]=0;
				num[j]=num[i]+1;
				d[j]=d[i]/num[j]*(num[j]+1);
				break;
			}
			mu[j]=-mu[i];
			num[j]=1;
			d[j]=d[i]*2;
		}
	}
}
