#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-5
#define MAXN 100009

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
double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}
double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}
bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > 0;
}
double angle(point a, point o, point b) {
	return acos(inner(a-o, b-o) / (dist(o,a)*dist(o,b)));
}

struct circle{
	point c;
	double r;
	circle() { c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	bool intersects(circle other) {
		return dist(c, other.c) < r + other.r;
	}
};

circle incircle( point p1, point p2, point p3 ) {
    double m1=dist(p2, p3);
    double m2=dist(p1, p3);
    double m3=dist(p1, p2);
    point c = (p1*m1+p2*m2+p3*m3)*(1/(m1+m2+m3));
    double s = 0.5*(m1+m2+m3);
    double r = sqrt(s*(s-m1)*(s-m2)*(s-m3))/s;
    return circle(c, r);
}

#define TREER (4000.0)

point getearcircle(point p, point q, point r) {
	
	double theta = angle(p, q, r);
	point p1 = (p-q).normalized();
	point p2 = (r-q).normalized();
	point pn = (p1+p2).normalized();
	double d = TREER / sin(theta/2.0);
	return q + (pn*d);
}

vector<point> P;
vector<point> C;
int N;

double distToLineSegment(point p, point a, point b) {
	double u = inner(p-a, b-a) / inner(b-a, b-a);
	if (u < 0.0) return dist(a, p);
	if (u > 1.0) return dist(b, p);
	return dist(a + ((b-a)*u), p);
}

bool checkcircle(point c) {
	for(int i=0; i<N; i++) {
		double d = distToLineSegment(c, P[i], P[(i+1)%N]);
		//printf("d = %.8f\n", d);
		if (d < TREER-EPS) return false;
	}
	return true;
}

int main() {
	scanf("%d", &N);
	double x, y;
	for(int i=0; i<N; i++) {
		scanf("%lf %lf", &x, &y);
		P.push_back(point(x, y));
	}
	
	double result = 0.0;
	for (int i = 0; i < N; i++) {
		result += cross(P[i], P[(i+1)%N]);
	}
	if (result < 0.0) reverse(P.begin(), P.end());
	
	for(int i=0; i<N; i++) {
		if (!ccw(P[i], P[(i+1)%N], P[(i+2)%N])) continue;
		point cur = getearcircle(P[i], P[(i+1)%N], P[(i+2)%N]);
		if (checkcircle(cur)) {
			C.push_back(cur);
		}
	}
	
	bool ok = false;
	point c1, c2;
	for(int i=0; i<(int)C.size(); i++) {
		for(int j=0; j<i && j<100; j++) {
			if (dist(C[i], C[j]) > 2*TREER - EPS) {
				ok = true;
				c1 = C[i];
				c2 = C[j];
			}
		}
	}
	
	if (ok) {
		printf("%.8f %.8f\n", c1.x, c1.y);
		printf("%.8f %.8f\n", c2.x, c2.y);
	}
	else printf("impossible\n");
	
	return 0;
}