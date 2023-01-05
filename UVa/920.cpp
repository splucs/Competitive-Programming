#include <cstdio>
#include <cmath>
#include <algorithm>
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

struct line {
	double a, b, c;
	line() { a = b = c = NAN;}
	line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
};

line pointsToLine(point p1, point p2) {
	line l;
	if (fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS){
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

bool areParallel(line l1, line l2) {
	return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

point intersection(line l1, line l2) {
	if (areParallel(l1, l2)) return point(NAN, NAN);
	point p;
	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
	else p.y = -(l2.a * p.x + l2.c);
	return p;
}


int main(){
	int C, N;
	point points[109], inter;
	scanf(" %d", &C);
	double level, ans, a, b;
	line aux, here;
	while(C-->0){
		scanf(" %d", &N);
		for(int i=0; i<N; i++){
			scanf(" %lf %lf", &a, &b);
			points[i] = point(a,b);
		}
		sort(points, points+N);
		level=points[N-1].y;
		ans = 0;
		for(int i=N-2; i>=0; i--){
			if (points[i].y>level){
				aux = pointsToLine(point(0.0, level), point(1.0, level));
				here = pointsToLine(points[i], points[i+1]);
				inter = intersection(aux, here);
				ans += dist(points[i], inter);
				level = points[i].y;
			}
		}
		printf("%.2f\n", ans);
	}
	return 0;
}