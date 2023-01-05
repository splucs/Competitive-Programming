#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

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

point closestToLineSegment(point p, point a, point b) {
	double u = inner(p-a, b-a) / inner(b-a, b-a);
	return a + ((b-a)*u);
}

double Lg, Lm;

bool solve(point p, point a, point b) {
	if (collinear(p, a, b)) {
		return dist(a, b) <= max(2.0*Lg, Lm) + EPS
			&& dist(a, p) <= max(2.0*Lg, Lm) + EPS
			&& dist(p, b) <= max(2.0*Lg, Lm) + EPS;
	}
	point pp = closestToLineSegment(p, a, b);
	if(dist(p, pp) <= Lm + EPS 
	&& dist(pp, b) <= Lg + EPS
	&& dist(pp, a) <= Lg + EPS)
		return true;
	if(dist(p, pp) <= Lg + EPS 
	&& dist(pp, b) <= Lm + EPS
	&& dist(pp, a) <= Lm + EPS
	&& inner(a-pp, b-pp) >= -EPS)
		return true;
	return false;
}


int main()
{
	int T;
	point p[3];
	bool possible;
	scanf("%d", &T);
	while(T--){
		scanf("%lf %lf", &Lm, &Lg);
		for(int i=0; i<3; i++) {
			scanf("%lf %lf", &p[i].x, &p[i].y);
		}
		possible = false;
		if (solve(p[0], p[1], p[2])) possible = true;
		if (solve(p[1], p[2], p[0])) possible = true;
		if (solve(p[2], p[0], p[1])) possible = true;
		if (possible) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}