#include <cstdio>
#include <cmath>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
using namespace std;
#define EPS 1e-5
#define MAXN 100009

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm() {
		return hypot(x, y);
	}
	point normalized() {
		return point(x,y)*(1.0/norm());
	}
	double angle() { return atan2(y, x);	}
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
	circle() { c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	double area() { return M_PI*r*r; }
	double chord(double rad) { return  2*r*sin(rad/2.0); }
	double sector(double rad) { return 0.5*rad*area()/M_PI; }
	bool intersects(circle other) {
		return dist(c, other.c) < r + other.r;
	}
	bool contains(point p) { return dist(c, p) <= r + EPS; }
	pair<point, point> getTangentPoint(point p) {
		double d1 = dist(p,c);
		double theta = asin(r/d1);
		point p1 = rotate(c-p,-theta);
		point p2 = rotate(c-p,theta);
		p1 = p1*(sqrt(d1*d1-r*r)/d1)+p;
		p2 = p2*(sqrt(d1*d1-r*r)/d1)+p;
		return make_pair(p1,p2);
	}
};

circle circumcircle(point a, point b, point c) {
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

circle incircle( point p1, point p2, point p3 ) {
    double m1=dist(p2, p3);
    double m2=dist(p1, p3);
    double m3=dist(p1, p2);
    point c = (p1*m1+p2*m2+p3*m3)*(1/(m1+m2+m3));
    double s = 0.5*(m1+m2+m3);
    double r = sqrt(s*(s-m1)*(s-m2)*(s-m3))/s;
    return circle(c, r);
}

//Minimum enclosing circle, O(n)
circle minimumCircle(vector<point> p) {
	random_shuffle(p.begin(), p.end());
	circle C = circle(p[0], 0.0);
	for(int i = 0; i < (int)p.size(); i++) {
		if (C.contains(p[i])) continue;
		C = circle(p[i], 0.0);
		for(int j = 0; j < i; j++) {
			if (C.contains(p[j])) continue;
			C = circle((p[j] + p[i])*0.5, 0.5*dist(p[j], p[i]));
			for(int k = 0; k < j; k++) {
				if (C.contains(p[k])) continue;
				C = circumcircle(p[j], p[i], p[k]);
			}
		}
	}
	return C;
}

int main()
{
	int n, c;
	scanf("%d", &c);
	vector<point> p;
	point t;
	while(c--) {
		scanf("%d", &n);
		p.clear();
		for(int i=0; i<n; i++) {
			scanf("%lf %lf", &t.x, &t.y);
			p.push_back(t);
		}
		circle mincir = minimumCircle(p);
		printf("%.2f\n%.2f %.2f\n", mincir.r, mincir.c.x, mincir.c.y);
	}
	return 0;
}
