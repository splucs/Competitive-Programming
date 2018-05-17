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
int leftmostIndex(vector<point> &P) {
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++) {
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}
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
vector<point> convexHull(vector<point> P) {
	int i, j, n = (int)P.size();
	if (n <= 3) {
		if (!(P[0] == P[n-1])) P.push_back(P[0]);
		return P;
	}
	int P0 = leftmostIndex(P);
	swap(P[0], P[P0]);
	pivot = P[0];
	sort(++P.begin(), P.end(), angleCmp);
	vector<point> S;
	S.push_back(P[n-1]);
	S.push_back(P[0]);
	S.push_back(P[1]);
	i = 2;
	while(i < n) {
		j = (int)S.size()-1;
		if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
		else S.pop_back();
	}
	return S;
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
