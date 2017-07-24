#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-4

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

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > 0;
}

bool collinear(point p, point q, point r) {
	return fabs(cross(p-q, r-p)) < EPS;
}

point rotate(point p, double rad) {
	return point(p.x * cos(rad) - p.y * sin(rad),
	p.x * sin(rad) + p.y * cos(rad));
}

double angle(point a, point o, point b) {
	return acos(inner(a-o, b-o) / (dist(o,a)*dist(o,b)));
}

point proj(point u, point v){
	return v*(inner(u,v)/inner(v,v));
}

bool between(point p, point q, point r) {
    return collinear(p, q, r) && inner(p - q, r - q) <= 0;
}

int leftmostIndex(vector<point> &P){
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++){
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}

double sqr(double x) {
	return x*x;
}

struct triangle{
	point a, b, c;
	triangle() { a = b = c = point(); }
	triangle(point _a, point _b, point _c) : a(_a), b(_b), c(_c) {}
	int isInside(point p){
		double u = cross(b-a,p-a)*cross(b-a,c-a);
		double v = cross(c-b,p-b)*cross(c-b,a-b);
		double w = cross(a-c,p-c)*cross(a-c,b-c);
		if (u > EPS && v > EPS && w > EPS) return 0;
		if (u < -EPS || v < -EPS || w < -EPS) return 2;
		else return 1;
	} //0 = inside/ 1 = border/ 2 = outside
};

int isInsideTriangle(point a, point b, point c, point p){
	return triangle(a,b,c).isInside(p);
} //0 = inside/ 1 = border/ 2 = outside

int main() {
	double a, b, c;
	while(scanf(" %lf %lf %lf", &a, &b, &c) != EOF) {
		double B = -sqr(a)-sqr(b)-sqr(c);
		double C = sqr(sqr(a))+sqr(sqr(b))+sqr(sqr(c))-sqr(a)*sqr(b)-sqr(b)*sqr(c)-sqr(c)*sqr(a);
		double delta = sqr(B) - 4*C;
		if (delta < 0) {
			printf("%.3f\n", -1.0);
			continue;
		}
		double l2 = (-B+sqrt(delta))/2.0;
		if (l2 < 0) {
			printf("%.3f\n", -1.0);
			continue;
		}
		double l = sqrt(l2);
		double S = sqr(l)*sqrt(3.0)/4.0;
		double x = (sqr(l)+sqr(b)-sqr(c))/(2.0*l);
		double y = (sqr(c) + sqr(l) + sqr(b) - 2.0*sqr(a))/(2.0*sqrt(3.0)*l);
		//printf("(x,y) = (%.3f,%.3f), l = %.3f\n", x, y, l);
		if (isInsideTriangle(point(0,0), point(l, 0), point(l/2.0, l*sqrt(3.0)/2.0), point(x, y)) != 2) {
			printf("%.3f\n", S);
		}
		else printf("%.3f\n", -1.0);
	}
	return 0;
}