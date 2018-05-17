#include <cstdio>
#include <cmath>
#define EPS 1e-9

struct point {
	double x, y, z;
	point() { x = y = z = 0.0; }
	point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	double norm() {
		return sqrt(x*x + y*y + z*z);
	}
	point normalized() {
		return point(x,y,z)*(1.0/norm());
	}
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else if (fabs(y - other.y) > EPS) return y < other.y;
		else return z < other.z;
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS && fabs(z - other.z) < EPS);
	}
	point operator +(point other) const{
		return point(x + other.x, y + other.y, z + other.z);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y, z - other.z);
	}
	point operator *(double k) const{
		return point(x*k, y*k, z*k);
	}
};

double dist(point p1, point p2) {
	return (p1-p2).norm();
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
	return cross(p-q, r-p).norm() < EPS;
}

double angle(point a, point o, point b) {
	return acos(inner(a-o, b-o) / (dist(o,a)*dist(o,b)));
}

point proj(point u, point v) {
	return v*(inner(u,v)/inner(v,v));
}