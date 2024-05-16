//迭代法实现
int exgcd(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - (a / b) * y;
	return d;
}

//非迭代法实现
int exgcd(int a, int b, int& x, int& y) {
	x = 1, y = 0;
	int x1 = 0, y1 = 1, a1 = a, b1 = b;
	while (b1) {
		int q = a1 / b1;
		tie(x, x1) = make_tuple(x1, x - q * x1);
		tie(y, y1) = make_tuple(y1, y - q * y1);
		tie(a1, b1) = make_tuple(b1, a1 - q * b1);
	}
	return a1;
}
