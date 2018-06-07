#include <cmath>
#include <algorithm>
using namespace std;
#define EPS 1e-9

/*
 * Auxiliary geometry objects
 */

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

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

point rotate(point p, double rad) {
	return point(p.x * cos(rad) - p.y * sin(rad),
	p.x * sin(rad) + p.y * cos(rad));
}

struct circle{
	point c;
	double r;
	circle() { c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	double chord(double rad) { return  2*r*sin(rad/2.0); }
	bool intersects(circle other) {
		return dist(c, other.c) < r + other.r;
	}
	bool contains(point p) { return dist(c, p) <= r + EPS; }
	pair<point, point> getTangentPoint(point p) {
		double d1 = dist(p, c), theta = asin(r/d1);
		point p1 = rotate(c-p,-theta);
		point p2 = rotate(c-p,theta);
		p1 = p1*(sqrt(d1*d1-r*r)/d1)+p;
		p2 = p2*(sqrt(d1*d1-r*r)/d1)+p;
		return make_pair(p1,p2);
	}
};

/*
 * Precision algorithms
 */
#include <vector>

struct StableSum {
	int cnt = 0;
	vector<double> v, pref(1, 0);
	void operator += (double a) { // a >= 0
		for (int s = ++cnt; s % 2 == 0; s >>= 1) {
			a += v.back();
			v.pop_back(), pref.pop_back();
		}
		v.push_back(a);
		pref.push_back(pref.back() + a);
	}
	double val() { return pref.back(); }
};

bool circleCircle(circle c1, circle c2, pair<point, point> & out) {
	double d = dist(c2.c, c1.c);
	double co = (d*d + c1.r*c1.r - c2.r*c2.r)/(2*d*c1.r);
	if (fabs(co) > 1.0) return false;
	double alpha = acos(co);
	point rad = (c2.c-c1.c)*(1.0/d*c1.r);
	out = {c1.c + rotate(rad, -alpha), c1.c + rotate(rad, alpha)};
	return true;
}

int quadRoots(double a, double b, double c, pair<double, double> &out) {
	if (fabs(a) < EPS) return 0;
	double delta = b*b - 4*a*c;
	if (delta < 0) return 0;
	double sum = (b >= 0) ? -b-sqrt(delta) : -b+sqrt(delta);
	out = {sum/(2*a), fabs(sum) > EPS ? 0 : (2*c)/sum};
	return 1 + (delta > 0);
}


/*
 * TEST MATRIX
 */
#include <cstdio>

int main() {
	double a, b, c;
	while(scanf("%lf %lf %lf", &a, &b, &c) != EOF) {
		pair<double, double> ans;
		int d = quadRoots(a, b, c, ans);
		printf("%d solutions for %.3fx^2 + %.3fx + %.3f:", d, a, b, c);
		if (d > 0) printf(" x = %.3f", ans.first);
		if (d > 1) printf(" x = %.3f", ans.second);
		printf("\n");
	}
	return 0;
}
