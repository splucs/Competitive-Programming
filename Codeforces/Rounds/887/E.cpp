#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-7
#define INF 1e+12
#define MAXN 100009

#define FOR(i, n) for(int (i)=0; (i)<(n); (i)++)
#define FOR1(i, n) for(int (i)=1; (i)<=(n); (i)++)
#define pb push_back

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm() {
		return hypot(x, y);
	}
	point normalized() {
		return point(x,y)*(1.0/norm());
	}
	double angle() { return atan2(y, x);	}
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

#define dist(p1, p2) hypot(p1.x - p2.x, p1.y - p2.y)

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}
double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

point A, B;

double getpos(point p, double dr) {
	point base = (A+B)*0.5;
	point n = B-A;
	n = point(-n.y, n.x);
	if (inner(n, p-base) < 0) n = n*(-1.0);
	n = n.normalized();

	double hi = INF;
	double lo = -INF;

	while(fabs(hi-lo) > EPS) {
		double mid = (hi+lo)*0.5;
		double x = base.x + (n.x*mid);
		double y = base.y + (n.y*mid);
		if (hypot(p.x-x, p.y-y) + dr < hypot(A.x-x, A.y-y)) hi = mid;
		else lo = mid;
	}
	
	point q = base + (n*((lo+hi)/2));
	double ans = dist(q, base);
	n = B-A;
	n = point(-n.y, n.x);
	if (inner(n, q-base) < 0) ans = -ans;
	return ans;
}

point cir[MAXN];
double r[MAXN];

typedef pair<double, double> dd;
dd intervals[MAXN];
double mx[MAXN];
int n;

int main() {
	double x1, y1, x2, y2;
	scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
	A = point(x1, y1);
	B = point(x2, y2);

	scanf("%d", &n);
	FOR(i, n) scanf("%lf %lf %lf", &cir[i].x, &cir[i].y, &r[i]);

	FOR(i, n) {
		double a = getpos(cir[i], -r[i]);
		double b = getpos(cir[i], r[i]);
		if (a > b) swap(a, b);
		intervals[i] = dd(a, b);
	}
	sort(intervals, intervals+n);
	FOR(i, n) {
		mx[i] = intervals[i].second;
		if (i > 0) mx[i] = max(mx[i], mx[i-1]);
	}

	double ans = INF;
	ans = min(ans, fabs(intervals[0].first));
	ans = min(ans, fabs(mx[n-1]));
	
	bool ok = true;
	FOR(i, n) {
		if (intervals[i].first < 0 && intervals[i].second > 0) ok = false;
	}
	if (ok) ans = 0;

	double last = -INF;
	FOR(i, n-1) {
		if (mx[i] <= intervals[i+1].first) {
			ans = min(ans, fabs(mx[i]));
			ans = min(ans, fabs(intervals[i+1].first));
		}
	}

	ans = hypot(ans, dist(A, B)/2);
	printf("%.10f\n", ans);

	return 0;
}