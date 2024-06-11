const double eps=1e-8; //精度，可按需要增加至1e-12之类的
int sign(double x){ //符号函数
	if(fabs(x)<eps) return 0;
	if(x<0) return -1;
	return 1;
}
int dcmp(double x,double y){ //比较函数
	if(fabs(x-y)<eps) return 0;
	if(x<y) return -1;
	return 1;
}

using PDD=pair<double,double>;
#define x first
#define y second

//基本运算符重载
PDD operator +(PDD a,PDD b){return PDD{a.x+b.x,a.y+b.y};}
PDD operator -(PDD a,PDD b){return PDD{a.x-b.x,a.y-b.y};}
PDD operator *(double k,PDD a){return PDD{k*a.x,k*a.y};}
PDD operator *(PDD a,double k){return PDD{k*a.x,k*a.y};}
PDD operator /(PDD a,double k){return PDD{a.x/k,a.y/k};}

double dot(PDD a,PDD b){ //内积
	return a.x*b.x+a.y*b.y;
}

double cross(PDD a,PDD b){ //叉积
	return a.x*b.y-b.x*a.y;
}

//取模（长度）
double get_length(PDD a){
	return sqrt(dot(a,a));
}

//计算向量夹角
double get_angle(PDD a,PDD b){
	return acos(dot(a,b)/get_length(a)/get_length(b));
}

//计算两个向量构成的平行四边形的面积
double area(PDD a,PDD b,PDD c){
	return cross(b-a,c-a);
}

//A绕原点**顺时针**旋转angle（弧度制）
PDD rotate(PDD a,double angle){
	return PDD{a.x*cos(angle) + a.y*sin(angle),
		-a.x*sin(angle) + a.y*cos(angle)};
}

//取直线p+vt, q+wt的交点
//cross(v,w)==0 则两直线平行或者重合，注意特判，这里没加特判
PDD get_line_inter(PDD p, PDD v, PDD q, PDD w){
	PDD u = p - q;
	double t = cross(w, u) / cross(v, w);
	return p + v * t;
}

//点p; 直线由a, b两点表示
//点到直线的距离
double dis2line(PDD p, PDD a, PDD b){
	PDD v1 = b - a, v2 = p - a;
	return fabs(cross(v1, v2) / get_length(v1));
}

//点到线段的距离
double dis2seg(PDD p, PDD a, PDD b){
	if (a == b) return get_length(p - a);
	PDD v1 = b - a, v2 = p - a, v3 = p - b;
	if (sign(dot(v1, v2)) < 0) return get_length(v2);
	if (sign(dot(v1, v3)) > 0) return get_length(v3);
	return dis2line(p, a, b);
}

//点在直线上的投影
PDD get_line_proj(PDD p, PDD a, PDD b){
	PDD v = b - a;
	return a + v * (dot(v, p - a) / dot(v, v));
}

//点是否在线段上
bool on_seg(PDD p, PDD a, PDD b){
	return sign(cross(p - a, p - b)) == 0 && sign(dot(p - a, p - b)) <= 0;
}

//判断两线段是否相交
bool seg_inter(PDD a1, PDD a2, PDD b1, PDD b2){
	double c1 = cross(a2-a1, b1-a1), c2 = cross(a2-a1, b2-a1);
	double c3 = cross(b2-b1, a1-b1), c4 = cross(b2-b1, a2-b1);
	// 有if则允许线段在端点处相交，无if则不允许，根据需要添加
	if(!sign(c1) && !sign(c2) && !sign(c3) && !sign(c4)){
		bool f1 = on_seg(b1, a1, a2);
		bool f2 = on_seg(b2, a1, a2);
		bool f3 = on_seg(a1, b1, b2);
		bool f4 = on_seg(a2, b1, b2);
		bool f = (f1|f2|f3|f4);
		return f;
	}
	return (sign(c1)*sign(c2) < 0 && sign(c3)*sign(c4) < 0);
}


//计算**任意**多边形面积（不一定凸）
double polygon_area(vector<PDD>p){
	double s = 0;
	for (int i = 1; i + 1 < p.size(); i ++ )
		s += cross(p[i] - p[0], p[i + 1] - p[i]);
	return s / 2;
}
