#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
double Rand(){return (long double)(rng())/UINT_MAX;}//生成一个[0,1]的小数
int Rand(int l,int r){return rng()%(r-l+1)+l;}//生成一个[l,r]的整数

//P1337
#define N 1010
int n,x[N],y[N],w[N];
double ansx,ansy,dis;

//calc返回能量值函数，在calc中更新答案
double calc(double xx,double yy){
	double res=0;
	for (int i=1;i<=n;i++){
		double dx=x[i]-xx,dy=y[i]-yy;
		res+=sqrt(dx*dx+dy*dy)*w[i];
	}
	if(res<dis) dis=res,ansx=xx,ansy=yy;
	return res;
}

void SA(){//simulated_annealing
	double nowx=ansx,nowy=ansy;
	double eps_t=1e-4;
	//模拟退火参数，起始温度，终止温度，每次乘以的系数
	for(auto t=2e5;t>eps_t;t*=0.99){
		double nxtx=nowx+t*(Rand()*2-1);
		double nxty=nowy+t*(Rand()*2-1);
		double delta=calc(nxtx,nxty)-calc(nowx,nowy);
		if(exp(-delta/t)>Rand()) nowx=nxtx,nowy=nxty;
	}
	//在得到的解附近多次随机状态，尝试得到更优的解
	for (int i=1;i<=1000;i++){
		double nxtx=ansx+eps_t*(Rand()*2-1);
		double nxty=ansy+eps_t*(Rand()*2-1);
		calc(nxtx,nxty);
	}
}

int main() {
	n=read();
	for(int i=1;i<=n;i++){
		x[i]=read(),y[i]=read(),w[i]=read();
		ansx+=x[i],ansy+=y[i];
	}
	ansx/=n,ansy/=n,dis=calc(ansx,ansy);
	//卡时技巧，填一个比题目时限略小的数
	while((double)clock()/CLOCKS_PER_SEC<0.9) SA();
	printf("%.3lf %.3lf\n", ansx, ansy);
	return 0;
}
