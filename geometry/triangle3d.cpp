#include <cstdio>
#include <cmath>
#define EPS 1e-9

struct point {
	double x, y, z;
	point() { x = y = z = 0.0; }
	point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	double norm() {
		return hypot(x, y, z);
	}
	point normalized() {
		return point(x, y, z)*(1.0 / norm());
	}
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else if (fabs(y - other.y) > EPS) return y < other.y;
		else return z < other.z;
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS && fabs(z - other.z) < EPS);
	}
	point operator +(point other) const {
		return point(x + other.x, y + other.y, z + other.z);
	}
	point operator -(point other) const {
		return point(x - other.x, y - other.y, z - other.z);
	}
	point operator *(double k) const {
		return point(x*k, y*k, z*k);
	}
};

double dist(point p1, point p2) {
	return (p1 - p2).norm();
}

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

point cross(point p1, point p2) {
	point ans;
	ans.x = p1.y*p2.z - p1.z*p2.y;
	ans.y = p1.z*p2.x - p1.x*p2.z;
	ans.z = p1.x*p2.y - p1.y*p2.x;
	return ans;
}

bool collinear(point p, point q, point r) {
	return cross(p - q, r - p).norm() < EPS;
}

double angle(point a, point o, point b) {
	return acos(inner(a - o, b - o) / (dist(o, a)*dist(o, b)));
}

point proj(point u, point v) {
	return v*(inner(u, v) / inner(v, v));
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
	double rCircumCircle() {
		return dist(a, b)*dist(b, c)*dist(c, a) / (4.0*area());
	}
	point normalVector() {
		return cross(y - x, z - x).normalized();
	}
	int isInside(point p) {
		point n = normalVector();
		double u = proj(cross(b - a, p - a), n).normalized()*proj(cross(b - a, c - a), n).normalized();
		double v = proj(cross(c - b, p - b), n).normalized()*proj(cross(c - b, a - b), n).normalized();
		double w = proj(cross(a - c, p - c), n).normalized()*proj(cross(a - c, b - c), n).normalized();
		if (fabs(u) < EPS || fabs(v) < EPS || fabs(w) < EPS) return 1;
		else if (u > 0.0 && v > 0.0 && w > 0.0) return 0;
		else return 2;
	} //0 = inside/ 1 = border/ 2 = outside
	int isProjInside(point p) {
		return isInside(p + proj(a - p, normalVector()));
	} //0 = inside/ 1 = border/ 2 = outside
};

double rInCircle(point a, point b, point c) {
	return triangle(a, b, c).rInCircle();
}

double rCircumCircle(point a, point b, point c) {
	return triangle(a, b, c).rCircumCircle();
}

int isProjInsideTriangle(point a, point b, point c, point p) {
	return triangle(a, b, c).isProjInside(p);
} //0 = inside/ 1 = border/ 2 = outside