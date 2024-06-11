#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
int n, pn, dq[20005], top, bot;
struct Point {
	double x, y;
} p[20005];

struct Line {
	Point a, b;
	double angle;
	Line& operator= (Line l) {
		a.x = l.a.x; a.y = l.a.y;
		b.x = l.b.x; b.y = l.b.y;
		angle = l.angle;
		return *this;
	}
} l[20005];

int dblcmp(double k) {
	if (fabs(k) < eps) return 0;
	return k > 0 ? 1 : -1;
}

double multi(Point p0, Point p1, Point p2) {
	return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}

bool cmp(const Line& l1, const Line& l2) {
	int d = dblcmp(l1.angle-l2.angle);
	if (!d) return dblcmp(multi(l1.a, l2.a, l2.b)) > 0; 
	return d < 0;
}

void addLine(Line& l, double x1, double y1, double x2, double y2) {
	l.a.x = x1; l.a.y = y1;
	l.b.x = x2; l.b.y = y2;
	l.angle = atan2(y2-y1, x2-x1);
}

void getIntersect(Line l1, Line l2, Point& p) {
	double A1 = l1.b.y - l1.a.y;
	double B1 = l1.a.x - l1.b.x;
	double C1 = (l1.b.x - l1.a.x) * l1.a.y - (l1.b.y - l1.a.y) * l1.a.x;
	double A2 = l2.b.y - l2.a.y;
	double B2 = l2.a.x - l2.b.x;
	double C2 = (l2.b.x - l2.a.x) * l2.a.y - (l2.b.y - l2.a.y) * l2.a.x;
	p.x = (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
	p.y = (C1 * A2 - C2 * A1) / (A1 * B2 - A2 * B1);
}

bool judge(Line l0, Line l1, Line l2) {
	Point p;
	getIntersect(l1, l2, p);
	return dblcmp(multi(p, l0.a, l0.b)) < 0;
}

void HalfPlaneIntersect( ){
	int i, j;
	sort(l, l+n, cmp);
	for (i = 0, j = 0; i < n; i++)
		if (dblcmp(l[i].angle-l[j].angle) > 0) 
			l[++j] = l[i];
	n = j + 1;
	dq[0] = 0; 
	dq[1] = 1;
	top = 1;   
	bot = 0;
	for (i = 2; i < n; i++) {
		while (top > bot && judge(l[i], l[dq[top]], l[dq[top - 1]])) top--;
		while (top > bot && judge(l[i], l[dq[bot]], l[dq[bot + 1]])) bot++;
		dq[++top] = i;
	} 
	while (top > bot && judge(l[dq[bot]], l[dq[top]], l[dq[top-1]])) top--;
	while (top > bot && judge(l[dq[top]], l[dq[bot]], l[dq[bot+1]])) bot++;
	dq[++top] = dq[bot]; 
	for (pn = 0, i = bot; i < top; i++, pn++)
		getIntersect(l[dq[i+1]], l[dq[i]], p[pn]);
}

double getArea() { 
	if (pn < 3) return 0;
	double area = 0;
	for (int i = 1; i < pn-1; i++)
		area += multi(p[0], p[i], p[i+1]);
	if (area < 0) area = -area;
	return area/2;
}

int main()
{
	int i;
	double x1, y1, x2, y2;
	
	while (scanf ("%d", &n) != EOF) {
		for (i = 0; i < n; i++) {
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			addLine(l[i], x1, y1, x2, y2);
		}
		addLine(l[n++], 0, 0, 10000, 0);
		addLine(l[n++], 10000, 0, 10000, 10000);
		addLine(l[n++], 10000, 10000, 0, 10000);
		addLine(l[n++], 0, 10000, 0, 0);
		HalfPlaneIntersect();
		printf ("%.1lf\n", getArea());
	}
	return 0;
}
