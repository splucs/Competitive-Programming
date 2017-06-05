#include <cstdio>
#include <cmath>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
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
double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}
double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

struct circle{
	point c;
	double r;
	circle(){ c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	double area() { return M_PI*r*r; }
	double chord(double rad) { return  2*r*sin(rad/2.0); }
	double sector(double rad) { return 0.5*rad*area()/M_PI; }
	bool contains(point p) { return dist(c, p) <= r + EPS; }
	bool isEnclosingCircle(point * p, int n){
		for(int i=0; i<n; i++){
			if (!contains(p[i])) return false;
		}
		return true;
	}
};

circle pointsToCircle(point a, point b, point c){
	circle ans;
	point u = point((b-a).y, -(b-a).x);
	point v = point((c-a).y, -(c-a).x);
	point n = (c-b)*0.5;
	double t = cross(u,n)/cross(v,u);
	ans.c = ((a+c)*0.5) + (v*t);
	ans.r = dist(ans.c, a);
	return ans;
}

int insideCircle(point p, circle c) {
	if (fabs(dist(p , c.c) - c.r)<EPS) return 1;
	else if (dist(p , c.c) < c.r) return 0;
	else return 2;
} //0 = inside/1 = border/2 = outside

circle minimumCircle(point * p, int n){
	if (n == 1) return circle(p[0], 0.0);
	random_shuffle(p, p+n);
	circle C = circle((p[0] + p[1])*0.5, 0.5*dist(p[0], p[1])), l, r, c, aux;
	point v, u, w;
	for(int i = 2; i < n; i++){
		if (C.contains(p[i])) continue;
		C = circle((p[0] + p[i])*0.5, 0.5*dist(p[0], p[i]));
		for(int j = 1; j<i; j++){
			if (C.contains(p[j])) continue;
			c = circle((p[j] + p[i])*0.5, 0.5*dist(p[j], p[i]));
			v = point((p[j] - p[i]).y, (p[i] - p[j]).x);
			u = c.c + v*(1e+20); l = circle(u, dist(u, p[i]));
			u = c.c - v*(1e+20); r = circle(u, dist(u, p[i]));
			for(int k=0; k<j; k++){
				aux = pointsToCircle(p[j], p[i], p[k]);
				u = aux.c - c.c; w = p[k] - c.c;
				if (inner(v, w) < 0 && inner(v, u) < inner(v, l.c - c.c)) l = aux;
				if (inner(v, w) > 0 && inner(v, u) > inner(v, r.c - c.c)) r = aux;
			}
			C = circle(c.c, 1e+20);
			if (c.isEnclosingCircle(p, j) && c.r < C.r) C = c;
			if (l.isEnclosingCircle(p, j) && l.r < C.r) C = l;
			if (r.isEnclosingCircle(p, j) && r.r < C.r) C = r;
		}
	}
	return C;
}

int main()
{
	int n;
	scanf("%d", &n);
	point p[309];
	for(int i=0; i<n; i++){
		scanf("%lf %lf", &p[i].x, &p[i].y);
	}
	circle mincir = minimumCircle(p, n);
	printf("%.2f\n", 2.0*mincir.r);
	return 0;
}