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

point lineIntersectSeg(point p, point q, point A, point B) {
	double c = cross(A-B, p-q);
	double a = cross(A, B);
	double b = cross(p, q);
	return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

/*
 * POLYGON 2D
 */

#include <vector>
#include <algorithm>
using namespace std;

typedef vector<point> polygon;

double signedArea(polygon & P) {
	double result = 0.0;
	int n = P.size();
	for (int i = 0; i < n; i++) {
		result += cross(P[i], P[(i+1)%n]);
	}
	return result / 2.0;
}

int leftmostIndex(vector<point> & P) {
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++) {
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}

polygon make_polygon(vector<point> P) {
	if (signedArea(P) < 0.0) reverse(P.begin(), P.end());
	int li = leftmostIndex(P);
	reverse(P.begin(), P.begin()+li);
	reverse(P.begin()+li, P.end());
	reverse(P.begin(), P.end());
	return P;
}

double perimeter(polygon & P) {
	double result = 0.0;
	for (int i = 0; i < (int)P.size()-1; i++) result += dist(P[i], P[i+1]);
	return result;
}

double area(polygon & P) {
	return fabs(signedArea(P));
}

bool isConvex(polygon & P) {
	int n = (int)P.size();
	if (n < 3) return false;
	bool left = ccw(P[0], P[1], P[2]);
	for (int i = 1; i < n; i++) {
		if (ccw(P[i], P[(i+1)%n], P[(i+2)%n]) != left)
			return false;
	}
	return true;
}

bool inPolygon(polygon & P, point p) {
	if (P.size() == 0u) return false;
	double sum = 0.0;
	int n = P.size();
	for (int i = 0; i < n; i++) {
		if (ccw(p, P[i], P[(i+1)%n])) sum += angle(P[i], p, P[(i+1)%n]);
		else sum -= angle(P[i], p, P[(i+1)%n]);
	}
	return fabs(fabs(sum) - 2*acos(-1.0)) < EPS;
}

polygon cutPolygon(polygon & P, point a, point b) {
	vector<point> R;
	double left1, left2;
	int n = P.size();
	for (int i = 0; i < n; i++) {
		left1 = cross(b-a, P[i]-a);
		left2 = cross(b-a, P[(i+1)%n]-a);
		if (left1 > -EPS) R.push_back(P[i]);
		if (left1 * left2 < -EPS) 
			R.push_back(lineIntersectSeg(P[i], P[(i+1)%n], a, b));
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
 * UVa 11265
 */

#include <cstdio>
#include <cassert>
int N;
double W, H;
point q;

int main() {
	int caseNo = 0;
	while(scanf("%d %lf %lf %lf %lf", &N, &W, &H, &q.x, &q.y) != EOF) {
		polygon P;
		P.push_back(point(0, 0));
		P.push_back(point(W, 0));
		P.push_back(point(W, H));
		P.push_back(point(0, H));
		for(int i = 0; i < N; i++) {
			point a, b;
			scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y);
			if (ccw(a, b, q)) P = cutPolygon(P, a, b);
			else P = cutPolygon(P, b, a);
			assert(isConvex(P));
			assert(inPolygon(P, q));

		}
		printf("Case #%d: %.3f\n", ++caseNo, area(P));
	}
	return 0;
}