#include <cstdio>
#include <cmath>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
using namespace std;
#define EPS 1e-9

/*
 * Point 2D
 */

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
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

point rotate(point p, double rad) {
	return point(p.x * cos(rad) - p.y * sin(rad),
	p.x * sin(rad) + p.y * cos(rad));
}

point closestToLineSegment(point p, point a, point b) {
	double u = inner(p-a, b-a) / inner(b-a, b-a);
	if (u < 0.0) return a;
	if (u > 1.0) return b;
	return a + ((b-a)*u);
}

double distToLineSegment(point p, point a, point b) {
	return dist(p, closestToLineSegment(p, a, b));
}

/*
 * Circle 2D
 */

struct circle {
	point c;
	double r;
	circle() { c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	double area() { return acos(-1.0)*r*r; }
	double chord(double rad) { return  2*r*sin(rad/2.0); }
	double sector(double rad) { return 0.5*rad*area()/acos(-1.0); }
	bool intersects(circle other) {
		return dist(c, other.c) < r + other.r;
	}
	bool contains(point p) { return dist(c, p) <= r + EPS; }
	pair<point, point> getTangentPoint(point p) {
		double d1 = dist(p, c), theta = asin(r/d1);
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

/*
 * Codeforces 101707B
 */
/*
point A, B;
circle C;

double getd2(point a, point b) {
	double h = dist(a, b);
	double r = C.r;
	double alpha = asin(h/(2*r));
	while (alpha < 0) alpha += 2*acos(-1.0);
	return dist(a, A) + dist(b, B) + r*2*min(alpha, 2*acos(-1.0) - alpha);
}

int main() {
	scanf("%lf %lf", &A.x, &A.y);
	scanf("%lf %lf", &B.x, &B.y);
	scanf("%lf %lf %lf", &C.c.x, &C.c.y, &C.r);
	double ans;
	if (distToLineSegment(C.c, A, B) >= C.r) {
		ans = dist(A, B);
	}
	else {
		pair<point, point> tan1 = C.getTangentPoint(A);
		pair<point, point> tan2 = C.getTangentPoint(B);
		ans = 1e+30;
		ans = min(ans, getd2(tan1.first, tan2.first));
		ans = min(ans, getd2(tan1.first, tan2.second));
		ans = min(ans, getd2(tan1.second, tan2.first));
		ans = min(ans, getd2(tan1.second, tan2.second));
	}
	printf("%.18f\n", ans);
	return 0;
}*/

/*
 * Codeforces 101707J
 */

vector<point> P;
int n;

int main () {
	scanf("%d", &n);
	P.resize(n);
	for(int i = 0; i < n; i++) {
		scanf("%lf %lf", &P[i].x, &P[i].y);
	}
	circle ans = minimumCircle(P);
	printf("%.18f %.18f\n%.18f\n", ans.c.x, ans.c.y, ans.r);
	return 0;
}