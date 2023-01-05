#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define MAXN 59

struct point {
	double x, y;
	point() { x = y = NAN; }
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

typedef pair<point, point> pp;

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

point closestToLineSegment(point p, point a, point b) {
	double u = inner(p-a, b-a) / inner(b-a, b-a);
	if (u < 0.0) return a;
	if (u > 1.0) return b;
	return a + ((b-a)*u);
}

struct circle{
	point c;
	double r;
	circle(){ c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	double area() { return M_PI*r*r; }
	double chord(double rad) { return  2*r*sin(rad/2.0); }
	double sector(double rad) { return 0.5*rad*area()/M_PI; }
	bool intersects(circle other){
		return dist(c, other.c) < r + other.r;
	}
	bool contains(point p) { return dist(c, p) <= r + EPS; }
	bool contains(circle other) { return dist(c, other.c) + other.r <= r + EPS; }
};

pp inter(circle c1, circle c2, double t) {
	double x1 = c1.c.x, y1 = c1.c.y, r1 = c1.r*t;
	double x2 = c2.c.x, y2 = c2.c.y, r2 = c2.r*t;
	double d = hypot(x1-x2, y1-y2);
	double l = (r1*r1 - r2*r2 + d*d)/(2*d);
	if (fabs(l) > fabs(r1)) make_pair(point(), point());
	double h = sqrt(r1*r1 - l*l);
	point i1 = point((l/d)*(x2-x1) + (h/d)*(y2-y1) + x1, (l/d)*(y2-y1) - (h/d)*(x2-x1) + y1);
	point i2 = point((l/d)*(x2-x1) - (h/d)*(y2-y1) + x1, (l/d)*(y2-y1) + (h/d)*(x2-x1) + y1);
	return make_pair(i1, i2);
}

bool intersects(circle c1, circle c2, circle c3, double t) {
	if (c1.contains(c2) && c2.intersects(c3)) return true;
	if (c2.contains(c1) && c1.intersects(c3)) return true;
	if (c2.contains(c3) && c3.intersects(c1)) return true;
	if (c3.contains(c2) && c2.intersects(c1)) return true;
	if (c3.contains(c1) && c1.intersects(c2)) return true;
	if (c1.contains(c3) && c3.intersects(c2)) return true;
	pp i1 = inter(c1, c2, t);
	pp i2 = inter(c1, c3, t);
	double theta1 = (i1.second-c1.c).angle();
	double theta2 = (i1.first-c1.c).angle();
	double theta3 = (i2.second-c1.c).angle();
	double theta4 = (i2.first-c1.c).angle();
	if (theta2 < theta1) theta2 += 2*M_PI;
	if (theta4 < theta3) theta4 += 2*M_PI;
	if (theta1 <= theta3 && theta3 <= theta2) return true;
	if (theta1 <= theta4 && theta4 <= theta2) return true;
	if (theta3 <= theta1 && theta1 <= theta4) return true;
	if (theta3 <= theta2 && theta2 <= theta4) return true;
	return false;
}

circle circles[MAXN];
int N;

bool check(double t) {
	for(int i=0; i<N; i++) {
		for(int j=0; j<i; j++) {
			for(int k=0; k<j; k++) {
				if (!intersects(circles[i], circles[j], circles[k], t))
					return false;
			}
		}
	}
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=0; i<N; i++) {
			scanf("%lf %lf %lf", &circles[i].c.x, &circles[i].c.y, &circles[i].r);
		}
		double lo = 0.0;
		double hi = 1e+8;
		while(hi-lo > EPS) {
			double mid = (hi+lo)/2.0;
			if (check(mid)) hi = mid;
			else lo = mid;
		}
		printf("%.6f\n", hi);
	}
	return 0;
}