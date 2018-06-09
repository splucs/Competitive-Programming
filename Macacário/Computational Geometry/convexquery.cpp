#include <bits/stdc++.h>
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

double dist(point a, point b) {
	return hypot(a.x-b.x, a.y-b.y);
}

double inner(point a, point b) {
	return a.x*b.x + a.y*b.y;
}

double cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > 0;
}

bool collinear(point p, point q, point r) {
	return fabs(cross(p-q, r-p)) < EPS;
}

/*
 * Triangle 2D
 */

struct triangle {
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

/*
 * Polygon 2D
 */

typedef vector<point> polygon;

int leftmostIndex(vector<point> &P) {
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++) {
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}

/*
 * Convex Hull
 */

point pivot(0, 0);

bool angleCmp(point a, point b) {
	if (collinear(pivot, a, b))
		return inner(pivot-a, pivot-a) < inner(pivot-b, pivot-b);
	return cross(a-pivot, b-pivot) >= 0;
}

polygon convexHull(vector<point> P) {
	int i, j, n = (int)P.size();
	if (n <= 2) return P;
	int P0 = leftmostIndex(P);
	swap(P[0], P[P0]);
	pivot = P[0];
	sort(++P.begin(), P.end(), angleCmp);
	vector<point> S;
	S.push_back(P[n-1]);
	S.push_back(P[0]);
	S.push_back(P[1]);
	for(i = 2; i < n;) {
		j = (int)S.size()-1;
		if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
		else S.pop_back();
	}
	reverse(S.begin(), S.end());
	S.pop_back();
	reverse(S.begin(), S.end());
	return S;
}

/*
 * Convex query
 */

bool query(polygon &P, point q) {
	int i = 1, j = P.size()-1, m;
	if (cross(P[i]-P[0], P[j]-P[0]) < -EPS)
		swap(i, j);
	while(abs(j-i) > 1) {
		int m = (i+j)/2;
		if (cross(P[m]-P[0], q-P[0]) < 0) j = m;
		else i = m;
	}
	return isInsideTriangle(P[0], P[i], P[j], q) != 2;
}

/*
 * Codeforces 101128J
 */

int main() {
	int nL, nS, nC;
	vector<point> L, S;
	scanf("%d", &nL);
	L.resize(nL);
	for(int i=0; i<nL; i++) {
		scanf("%lf %lf", &L[i].x, &L[i].y);
	}
	scanf("%d", &nS);
	S.resize(nS);
	for(int i=0; i<nS; i++) {
		scanf("%lf %lf", &S[i].x, &S[i].y);
	}
	L = convexHull(L);
	int ans = 0;
	for(int i=0; i<nS; i++) {
		if (query(L, S[i])) {
			//printf("(%f,%f) inside\n", S[i].x, S[i].y);
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
