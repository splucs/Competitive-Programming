#include <cstdio>
#include <cmath>
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
	double angle() { return atan2(y, x); }
	double polarAngle() {
		double a = atan2(y, x);
		return a < 0 ? a + 2*acos(-1.0) : a;
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

/*
 * POLYGON 2D
 */

#include <vector>
#include <algorithm>
using namespace std;

point lineIntersectSeg(point p, point q, point A, point B) {
	double c = cross(A-B, p-q);
	double a = cross(A, B);
	double b = cross(p, q);
	return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

typedef vector<point> polygon;

double perimeter(polygon & P) {
	double result = 0.0;
	for (int i = 0; i < (int)P.size()-1; i++) result += dist(P[i], P[i+1]);
	return result;
}

double signedArea(polygon & P) {
	double result = 0.0;
	for (int i = 0; i < (int)P.size()-1; i++) {
		result += cross(P[i], P[i+1]);
	}
	return result/2.0;
}

double area(polygon & P) {
	return fabs(signedArea(P));
}

bool isConvex(polygon & P) {
	int sz = (int)P.size();
	if (sz <= 3) return false;
	bool isLeft = ccw(P[0], P[1], P[2]);
	for (int i = 1; i < sz-1; i++) {
		if (ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft)
			return false;
	}
	return true;
}
bool inPolygon(polygon & P, point p) {
	if (P.size() == 0u) return false;
	double sum = 0.0;
	for (int i = 0; i < (int)P.size()-1; i++) {
		if (ccw(p, P[i], P[i+1])) sum += angle(P[i], p, P[i+1]);
		else sum -= angle(P[i], p, P[i+1]);
	}
	return fabs(fabs(sum) - 2*acos(-1.0)) < EPS;
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

polygon cutPolygon(polygon P, point a, point b) {
	vector<point> R;
	double left1, left2;
	for (int i = 0; i < (int)P.size(); i++) {
		left1 = cross(b-a, P[i]-a);
		if (i != (int)P.size()-1) left2 = cross(b-a, P[i+1]-a);
		else left2 = 0;
		if (left1 > -EPS) R.push_back(P[i]);
		if (left1 * left2 < -EPS)
			R.push_back(lineIntersectSeg(P[i], P[i+1], a, b));
	}
	return make_polygon(R);
}

#define INF 1e10

//Código levemente modificado em comparação ao presente no line2d.cpp
point segIntersects(point a, point b, point p, point q) {
    point u = b-a, v = q-p;
    if (fabs(cross(v, u)) < EPS)
		return point(-INF - 1, -INF - 1);
    ld k1 = (cross(a, v) - cross(p, v)) / cross(v, u);
    ld k2 = (cross(a, u) - cross(p, u)) / cross(v, u);
    if (k1 >= 0 && k1 <= 1 && k2 >= 0 && k2 <= 1)return a + u * k1;
    return point(-INF - 1, -INF - 1);
}

point pivot(0, 0);

bool angleCmp(point a, point b) {
	if (collinear(pivot, a, b)) return inner(pivot-a, pivot-a) < inner(pivot-b, pivot-b);
	return cross(a-pivot, b-pivot) >= 0;
}

polygon intersects(polygon &A, polygon &B){
	polygon P;

	for (int i = 0; i < (int) A.size() - 1; ++i){
		if (inPolygon(B, A[i])) P.push_back(A[i]);
		for (int j = 0; j < (int) B.size() - 1; ++j){
			point p = segIntersects(A[i], A[i + 1], B[j], B[j + 1]);
			if (p.x > -INF) P.push_back(p);
		}
	}
	for (int i = 0; i < (int) B.size() - 1; ++i){
		if (inPolygon(A, B[i])) P.push_back(B[i]);
	}
	//Remove duplicates
	set<point> inuse;
	
	int u = 0;
	for (int i = 0; i < (int) P.size(); ++i){
		if (inuse.count(P[i])) continue;
		inuse.insert(P[i]);
		P[u++] = P[i];
	}
	while (u != P.size()) P.pop_back();
	//End removal
	
	if (!P.empty()){
		pivot = P[0];
		sort(P.begin(), P.end(), angleCmp);
		P.push_back(P[0]);
	}
	return P;
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
	/*printf("intersection:\n");
	m = polyintersect(polygon(p1), polygon(p2)).P;
	for(int i=0; i<(int)m.size(); i++) {
		printf("%.2f %.2f\n", m[i].x, m[i].y);
	}*/
	return true;
}

int main()
{
	test();
	return 0;
}
