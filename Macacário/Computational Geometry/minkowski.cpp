#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
#define EPS 1e-9

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
	double polarAngle() {
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

point proj(point u, point v) {
	return v*(inner(u,v)/inner(v,v));
}

bool between(point p, point q, point r) {
    return collinear(p, q, r) && inner(p - q, r - q) <= 0;
}

int leftmostIndex(vector<point> &P) {
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++) {
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}

/*
 * POLYGON 2D
 */

#include <algorithm>

typedef vector<point> polygon;

double signedArea(polygon & P) {
	double result = 0.0;
	for (int i = 0; i < (int)P.size()-1; i++) {
		result += cross(P[i], P[i+1]);
	}
	return result/2.0;
}

polygon make_polygon(vector<point> P) {
	if (!P.empty() && !(P.back() == P.front()))
		P.push_back(P[0]);
	if (signedArea(P) < 0.0) {
		for(int i = 0; 2*i < (int)P.size(); i++) {
			swap(P[i], P[P.size()-i-1]);
		}
	}
	return P;
}

/*
 * MINKOWSKI
 */

polygon minkowski(polygon A, polygon B) {
	polygon P;
	A.pop_back(); B.pop_back();
	int s1 = leftmostIndex(A), n1 = A.size();
	int s2 = leftmostIndex(B), n2 = B.size();
	P.push_back(A[s1]+B[s2]);
	int i=s1+1, j=s2+1, c1=0, c2=0;
	point v1, v2;
	while(c1 < n1 || c2 < n2) {
		v1 = A[i]-A[(i-1+n1)%n1];
		v2 = B[j]-B[(j-1+n2)%n2];
		if (c2 == n2 || (c1 < n1 && cross(v1, v2) > 0)) {
			P.push_back(P.back() + v1);
			i = (i+1)%n1; c1++;
		}
		else if (c1 == n1 || (c2 < n2 && cross(v1, v2) < 0)) {
			P.push_back(P.back() + v2);
			j = (j+1)%n2; c2++;
		}
		else {
			P.push_back(P.back() + (v1+v2));
			i = (i+1)%n1; c1++;
			j = (j+1)%n2; c2++;
		}
	}
	return make_polygon(P);
}

/*
 * TEST MATRIX
 */
 
bool test() {
	int n;
	double x, y;
	vector<point> p1, p2, m;
	printf("insert polygon 1:\n");
	scanf("%d", &n);
	while(n--) {
		scanf("%lf %lf", &x, &y);
		p1.push_back(point(x, y));
	}
	printf("insert polygon 2:\n");
	scanf("%d", &n);
	while(n--) {
		scanf("%lf %lf", &x, &y);
		p2.push_back(point(x, y));
	}
	printf("minkowski sum:\n");
	m = minkowski(make_polygon(p1), make_polygon(p2));
	for(int i=0; i<(int)m.size(); i++) {
		printf("%.2f %.2f\n", m[i].x, m[i].y);
	}
	return true;
}

/*
 * Codeforces 87E
 */

struct triangle{
	point a, b, c;
	triangle() { a = b = c = point(); }
	triangle(point _a, point _b, point _c) : a(_a), b(_b), c(_c) {}
	int isInside(point p) {
		double u = cross(b-a,p-a)*cross(b-a,c-a);
		double v = cross(c-b,p-b)*cross(c-b,a-b);
		double w = cross(a-c,p-c)*cross(a-c,b-c);
		if (u > 0.0 && v > 0.0 && w > 0.0) return 0;
		if (u < 0.0 || v < 0.0 || w < 0.0) return 2;
		else return 1;
	} //0 = inside/ 1 = border/ 2 = outside
};
int isInsideTriangle(point a, point b, point c, point p) {
	return triangle(a,b,c).isInside(p);
} //0 = inside/ 1 = border/ 2 = outside
point pivot(0,0);
bool angleCmp(point a, point b) {
	if (collinear(pivot, a, b)) return dist(pivot, a) < dist(pivot, b);
	double d1x = a.x-pivot.x, d1y = a.y-pivot.y;
	double d2x = b.x-pivot.x, d2y = b.y-pivot.y;
	return atan2(d1y, d1x) - atan2(d2y, d2x) < 0;
}
bool query(vector<point> &CH, point q) {
	int i = 2, j = CH.size()-1, m;
	pivot = CH[1];
	while(j > i+1) {
		int m = (i+j)/2;
		if (angleCmp(q, CH[m])) j = m;
		else i = m;
	}
	return isInsideTriangle(pivot, CH[i], CH[j], q) != 2;
}

void printpolygon(polygon & P) {
	printf("printing polygon:\n");
	for(int i=0; i<(int)P.size(); i++) {
		printf("%.2f %.2f\n", P[i].x, P[i].y);
	}
}

int main()
{
	polygon city[3], sum;
	vector<point> P;
	double x, y;
	for(int i=0, n; i<3; i++) {
		scanf("%d", &n);
		P.clear();
		while(n--) {
			scanf("%lf %lf", &x, &y);
			P.push_back(point(x, y));
		}
		city[i] = make_polygon(P);
	}
	sum = minkowski(city[0], city[1]);
	sum = minkowski(sum, city[2]);
		//printpolygon(sum);
	P = sum;
	for(int i=(int)P.size()-1; i>0; i--) {
		P[i] = P[i-1];
	}
	P[0] = P.back();
	//printpolygon(polygon(P));
	int m;
	scanf("%d", &m);
	while(m--) {
		scanf("%lf %lf", &x, &y);
		if (query(P, point(x, y)*3.0)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}