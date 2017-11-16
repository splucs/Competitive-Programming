#include <cstdio>
#include <cmath>
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

void read(point & p){
	scanf("%lf %lf", &p.x, &p.y);
}

int main(){
	point D, p1, p2;
	read(D);
	int N, ans = 0;
	scanf("%d", &N);
	while(N--){
		read(p1);
		read(p2);
		if (fabs(cross(p1-p2, D)) < EPS){
			if (fabs(cross(p1, p2)) > EPS) continue;
			if (inner(p1, D)*inner(p2, D) < -EPS){
				ans++;
				continue;
			}
		}
		double k = cross(D, p2)/(cross(p1-p2, D));
		double lambda = inner(D, (p1*k) + (p2*(1.0-k)))/(D.norm()*D.norm());
		if (k > EPS && k < 1.0-EPS && lambda > EPS) ans++;
	}
	printf("%d\n", ans);
	return 0;
}