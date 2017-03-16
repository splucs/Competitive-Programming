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

int insideCircle(point p, circle c) {
	if (fabs(dist(p, c.c) - c.r)<EPS) return 1;
	else if (dist(p, c.c) < c.r) return 0;
	else return 2;
} //0 = inside/1 = border/2 = outside

circle incircle(point p1, point p2, point p3) {
	double m1 = dist(p2, p3);
	double m2 = dist(p1, p3);
	double m3 = dist(p1, p2);
	point c = (p1*m1 + p2*m2 + p3*m3)*(1 / (m1 + m2 + m3));
	double s = 0.5*(m1 + m2 + m3);
	double K = sqrt(s*(s - m1)*(s - m2)*(s - m3));
	double r = K / s;
	return circle(c, r);
}