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

struct line {
	point r;
	point v;
	line(point _r, point _v) {
		v = _v; r = _r;
	}
	bool operator == (line other) const {
		return fabs(cross(r - other.r, v).norm()) < EPS && fabs(cross(r - other.r, other.v).norm()) < EPS;
	}
};

point distVector(line l, point p) {
	point dr = p - l.r;
	return dr - proj(dr, l.v);
}

point distVectorBasePoint(line l, point p) {
	return proj(p - l.r, l.v) + l.r;
}

point distVectorEndPoint(line l, point p) {
	return p;
}

point distVector(line a, line b) {
	point dr = b.r - a.r;
	point n = cross(a.v, b.v);
	if (n.norm() < EPS) {
		return dr - proj(dr, a.v);
	}
	else return proj(dr, n);
}

double dist(line a, line b) {
	return distVector(a, b).norm();
}

point distVectorBasePoint(line a, line b) {
	if (cross(a.v, b.v).norm() < EPS) return a.r;
	point d = distVector(a, b);
	double lambda;
	if (fabs(b.v.x*a.v.y - a.v.x*b.v.y) > EPS)
		lambda = (b.v.x*(b.r.y - a.r.y - d.y) - b.v.y*(b.r.x - a.r.x - d.x)) / (b.v.x*a.v.y - a.v.x*b.v.y);
	else if (fabs(b.v.x*a.v.z - a.v.x*b.v.z) > EPS)
		lambda = (b.v.x*(b.r.z - a.r.z - d.z) - b.v.z*(b.r.x - a.r.x - d.x)) / (b.v.x*a.v.z - a.v.x*b.v.z);
	else if (fabs(b.v.z*a.v.y - a.v.z*b.v.y) > EPS)
		lambda = (b.v.z*(b.r.y - a.r.y - d.y) - b.v.y*(b.r.z - a.r.z - d.z)) / (b.v.z*a.v.y - a.v.z*b.v.y);
	return a.r + (a.v*lambda);
}

point distVectorEndPoint(line a, line b) {
	return distVectorBasePoint(a, b) + distVector(a, b);
}