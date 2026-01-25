namespace Comb{ // combination
	constexpr int N=TODO;
	constexpr int M=TODO;
	Z c[N][M];
	void init(){
		c[0][0]=raw(1);
		for(int i=1;i<N;i++){
			c[i][0]=raw(1);
			for(int j=1;j<M && j<=i;j++){
				c[i][j]=c[i-1][j-1]+c[i-1][j];
			}
		}
	}
}
using Comb::c;

Comb::init(); // 初始化