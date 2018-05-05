#include <bits/stdc++.h>
using namespace std;
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

int main() {
	point c1, c2;
	double r1, r2;
	scanf("%lf %lf %lf", &c1.x, &c1.y, &r1);
	scanf("%lf %lf %lf", &c2.x, &c2.y, &r2);
	point a1 = c1 + ((c2-c1).normalized()*r1);
	point a2 = c2 + ((c1-c2).normalized()*r2);
	point ans;
	if (dist(c1, c2) < r1) ans = c2;
	else if (dist(c1, c2) < r2) ans = c1;
	else ans = (a1+a2)*0.5;
	printf("%.6f %.6f\n", ans.x, ans.y);
	return 0;
}