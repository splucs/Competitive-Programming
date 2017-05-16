#include <bits/stdc++.h>
using namespace std;
#define MAXN 29
#define EPS 1e-9

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm(){
		return hypot(x, y);
	}
	point normalized(){
		return point(x,y)*(1.0/norm());
	}
	double angle(){ return atan2(y, x);	}
	double polarAngle(){
		double a = atan2(y, x);
		return a < 0 ? a + 2*M_PI : a;
	}
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else return y < other.y;
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
	}
	point operator +(point other) const{
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y);
	}
	point operator *(double k) const{
		return point(x*k, y*k);
	}
};

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

int n;
double L[MAXN], sum[MAXN];

double sqr(double x) {
	return x*x;
}

point intersect(point p1, point p2, double s, double l) {
	double d = dist(p1, p2);
	//printf("d=%.4f s=%.4f l=%.4f\n", d, s, l);
	if (fabs(d) < EPS) return p1 + (point(1, 0)*s);
	if (fabs(s) < EPS) return p1;
	if (fabs(l) < EPS) return p1 + ((p2-p1).normalized()*s);
	if (d >= s+l - EPS) return p1 + ((p2-p1).normalized()*s);
	if (l >= d+s - EPS) return p1 - ((p2-p1).normalized()*s);
	if (s >= d+l - EPS) return p1 + ((p2-p1).normalized()*s);
	double x0 = p2.x-p1.x;
	double y0 = p2.y-p1.y;
	double D2 = sqr(s) + sqr(x0) + sqr(y0) - sqr(l);
	double a = 4*(sqr(x0) + sqr(y0));
	double b = -4*D2*x0;
	double c = sqr(D2) - 4*sqr(y0)*sqr(s);
	double delta = b*b - 4*a*c;
	//if (delta < 0) printf("error, negative delta\n");
	double x1 = (-b + sqrt(delta))/(2*a);
	double x2 = (-b - sqrt(delta))/(2*a);
	double x, y;
	if (fabs(x1) < fabs(x2)) x = x1;
	else x = x2;
	//if (fabs(x) > s) printf("error, no possible y\n");
	y = sqrt(s*s - x*x);
	return p1 + point(x, y);
	
}
	
int main() {
	scanf("%d", &n);
	sum[0]=0;
	for(int i=1; i<=n; i++) {
		scanf(" %lf", &L[i]);
		sum[i] = L[i] + sum[i-1];
	}
	point dest;
	double x, y;
	scanf(" %lf %lf", &x, &y);
	dest = point(x, y);
	point cur = point(0, 0);
	vector<point> ans;
	ans.push_back(point(0, 0));
	for(int i=1; i<=n; i++) {
		cur = intersect(cur, dest, L[i], sum[n] - sum[i]);
		printf("%.3f %.3f\n", cur.x, cur.y);
		ans.push_back(cur);
	}
	for(int i=1; i<=n; i++){
		printf("dist[(%.4f,%.4f),(%.4f,%.4f)] = %.4f, L[%d] = %.4f\n", ans[i-1].x, ans[i-1].y, ans[i].x, ans[i].y, dist(ans[i], ans[i-1]), i, L[i]);
		if (fabs(dist(ans[i], ans[i-1]) - L[i]) > EPS) printf("Wrong answer %d\n", i);
	}
	return 0;
}