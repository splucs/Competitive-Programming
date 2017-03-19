#include <vector>
#include <cstdio>
#include <cmath>
#define EPS 1e-9
using namespace std;

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

bool ccw(point p, point q, point r) {
	return cross(q - p, r - p) > 0;
}

bool collinear(point p, point q, point r) {
	return fabs(cross(p - q, r - p)) < EPS;
}

point lineIntersectSeg(point p, point q, point A, point B) {
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c);
	return point((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v));
}

struct polygon {
	vector<point> P;
	polygon() {
		P.clear();
	}
	polygon(vector<point> Q) {
		P.clear();
		for (int i = 0; i<(int)Q.size(); i++) {
			P.push_back(Q[i]);
		}
		if (!Q.empty() && !(Q.back() == Q.front()))
			P.push_back(Q[0]);
	}
	double perimeter() {
		double result = 0.0;
		for (int i = 0; i < (int)P.size() - 1; i++) result += dist(P[i], P[i + 1]);
		return result;
	}
	double area() {
		double result = 0.0;
		for (int i = 0; i < (int)P.size() - 1; i++) {
			result += (P[i].x*P[i + 1].y - P[i + 1].x*P[i].y);
		}
		return fabs(result) / 2.0;
	}
	bool isConvex() {
		int sz = (int)P.size();
		if (sz <= 3) return false;
		bool isLeft = ccw(P[0], P[1], P[2]);
		for (int i = 1; i < sz - 1; i++) {
			if (ccw(P[i], P[i + 1], P[(i + 2) == sz ? 1 : i + 2]) != isLeft)
				return false;
		}
		return true;
	}
	bool inPolygon(point pt) {
		if ((int)P.size() == 0) return false;
		double sum = 0;
		for (int i = 0; i < (int)P.size() - 1; i++) {
			if (ccw(pt, P[i], P[i + 1])) sum += angle(P[i], pt, P[i + 1]);
			else sum -= angle(P[i], pt, P[i + 1]);
		}
		return fabs(fabs(sum) - 2 * PI) < EPS;
	}
	polygon cutPolygon(point a, point b) {
		vector<point> R;
		double left1, left2;
		for (int i = 0; i < (int)P.size(); i++) {
			left1 = cross(b - a, P[i] - a);
			if (i != (int)P.size() - 1) left2 = cross(b - a, P[i + 1] - a);
			else left2 = 0;
			if (left1 > -EPS) P.push_back(P[i]);
			if (left1 * left2 < -EPS)
				R.push_back(lineIntersectSeg(P[i], P[i + 1], a, b));
		}
		return polygon(R);
	}
};