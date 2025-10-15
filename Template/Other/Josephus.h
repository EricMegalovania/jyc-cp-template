// josephus, index start from 0
// 0,1,...,k-1, k-1 is deleted
int jose(int n,int k){ // O(n)
	int x=0;
	for(int i=1;i<=n;++i) x=(x+k)%i;
	return x;
}
LL josell(LL n,int k){ // O(k*logn)
	if(n==1) return 0;
	if(k==1) return n-1;
	if(k>n) return (josell(n-1,k)+k)%n;
	LL res=josell(n-n/k,k);
	res-=n%k;
	if(res<0) res+=n;
	else res+=res/(k-1);
	return res;
}
