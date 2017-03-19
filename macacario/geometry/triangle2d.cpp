#include <cstdio>
#include <cmath>
#define EPS 1e-9

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm() { return hypot(x, y); }
	point normalized() {
		return point(x, y)*(1.0 / norm());
	}
	double angle() { return atan2(y, x); }
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS)
			return x < other.x;
		else return y < other.y;
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
	}
	point operator +(point other) const {
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const {
		return point(x - other.x, y - other.y);
	}
	point operator *(double k) const {
		return point(x*k, y*k);
	}
};

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

struct circle {
	point c;
	double r;
	circle() { c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	double area() { return M_PI*r*r; }
	double chord(double rad) { return  2 * r*sin(rad / 2.0); }
	double sector(double rad) { return 0.5*rad*area() / M_PI; }
	bool intersects(circle other) {
		return dist(c, other.c) < r + other.r;
	}
	bool contains(point p) { return dist(c, p) <= r + EPS; }
	bool isEnclosingCircle(vector<point> & p, int n) {
		for (int i = 0; i<n; i++) {
			if (!contains(p[i])) return false;
		}
		return true;
	}
};

circle circumcircle(point a, point b, point c) {
	circle ans;
	point u = point((b - a).y, -(b - a).x);
	point v = point((c - a).y, -(c - a).x);
	point n = (c - b)*0.5;
	double t = cross(u, n) / cross(v, u);
	ans.c = ((a + c)*0.5) + (v*t);
	ans.r = dist(ans.c, a);
	return ans;
}

struct line {
	double a, b, c;
	line() { a = b = c = NAN; }
	line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
};

line pointsToLine(point p1, point p2) {
	line l;
	if (fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS) {
		l.a = l.b = l.c = NAN;
	}
	else if (fabs(p1.x - p2.x) < EPS) {
		l.a = 1.0; l.b = 0.0; l.c = -p1.x;
	}
	else {
		l.a = -(p1.y - p2.y) / (p1.x - p2.x);
		l.b = 1.0;
		l.c = -(l.a * p1.x) - p1.y;
	}
	return l;
}

struct triangle {
	point a, b, c;
	triangle() { a = b = c = point(); }
	triangle(point _a, point _b, point _c) : a(_a), b(_b), c(_c) {}
	double perimeter() { return dist(a, b) + dist(b, c) + dist(c, a); }
	double semiPerimeter() { return perimeter() / 2.0; }
	double area() {
		double s = semiPerimeter(), ab = dist(a, b),
			bc = dist(b, c), ca = dist(c, a);
		return sqrt(s*(s - ab)*(s - bc)*(s - ca));
	}
	double rInCircle() {
		return area() / semiPerimeter();
	}
	circle inCircle() {
		circle ans;
		ans.r = rInCircle();
		if (fabs(ans.r) < EPS) return circle(point(NAN, NAN), NAN);
		line l1, l2;
		double ratio = dist(a, b) / dist(a, c);
		point p = b + ((c - b)*(ratio / (1 + ratio)));
		l1 = pointsToLine(a, p);
		ratio = dist(b, a) / dist(b, c);
		p = a + ((c - a)*(ratio / (1 + ratio)));
		l2 = pointsToLine(b, p);
		ans.c = intersection(l1, l2);
		return ans;
	}
	double rCircumCircle() {
		return dist(a, b)*dist(b, c)*dist(c, a) / (4.0*area());
	}
	circle circumCircle() {
		return circumcircle(a, b, c);
	}
	int isInside(point p) {
		double u = cross(b - a, p - a)*cross(b - a, c - a);
		double v = cross(c - b, p - b)*cross(c - b, a - b);
		double w = cross(a - c, p - c)*cross(a - c, b - c);
		if (fabs(u) < EPS || fabs(v) < EPS || fabs(w) < EPS) return 1;
		else if (u > 0.0 && v > 0.0 && w > 0.0) return 0;
		else return 2;
	} //0 = inside/ 1 = border/ 2 = outside
};