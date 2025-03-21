//Primitive Pythagorean triples
unordered_map<int,vector<ai2>>flag;
void init(){ //(x,y,z) x<y<N
	//(i^2-j^2)^2 + (2ij)^2 = (i^2+j^2)^2
	for(int j=1;2*j*j<N;j++){
		for(int i=j+1;i*i-j*j<N;i++) if((i-j)&1 && gcd(i,j)==1){
			int x=i*i-j*j,y=2*i*j,z=i*i+j*j;
			if(x>y) swap(x,y);
			for(int k=1;k*y<N;k++){
				flag[k*z].push_back({k*x,k*y});
			}
		}
	}
}
