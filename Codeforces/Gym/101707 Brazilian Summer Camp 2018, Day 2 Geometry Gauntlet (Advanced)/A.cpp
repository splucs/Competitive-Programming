#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 200309
#define MAXM 900009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

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

bool parallel(point p, point q) {
	return fabs(cross(p, q)) < EPS;
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
    return collinear(p, q, r) && inner(p - q, r - q) <= EPS;
}

point lineIntersectSeg(point p, point q, point A, point B) {
	double c = cross(A-B, p-q);
	double a = cross(A, B);
	double b = cross(p, q);
	return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

point A1, A2, B1, B2, V;

bool caseStopped() {
	if (fabs(V.x) < EPS && fabs(V.y) < EPS) {
		printf("-1\n");
		return true;
	}
	else return false;
}

bool caseParallel() {
	if (!parallel(A2-A1, B2-B1) || !parallel(A2-A1, V)) return false;
	if (!parallel(A2-A1, A1-B1)) {
		printf("-1\n");
		return true;
	}
	point A = dist(A1, B1) > dist(A2, B1) ? A2 : A1;
	point B = dist(B1, A1) > dist(B2, A1) ? B2 : B1;
	if (fabs(V.x) < EPS && fabs(V.y) < EPS || inner(A-B, V) < EPS) {
		printf("-1\n");
		return true;
	}
	printf("%.10f\n", dist(A, B) / V.norm());
	return true;
}

bool caseParallelSpeed() {
	if (parallel(A2-A1, V)) {
		swap(A1, B1);
		swap(A2, B2);
		V = V*(-1.0);
	}
	if (!parallel(B2-B1, V)) return false;
	point q = lineIntersectSeg(A1, A2, B1, B2);
	if (!between(A1, q, A2)) {
		printf("-1\n");
		return true;
	}
	point A = q;
	point B = dist(B1, q) > dist(B2, q) ? B2 : B1;
	if (fabs(V.x) < EPS && fabs(V.y) < EPS || inner(A-B, V) < EPS) {
		printf("-1\n");
		return true;
	}
	printf("%.10f\n", dist(A, B) / V.norm());
	return true;
}

bool generalCase() {
	point p1 = lineIntersectSeg(A1, A2, B1, B1+V);
	point p2 = lineIntersectSeg(A1, A2, B2, B2+V);
	double t1 = inner(p1-A1, A2-A1)/inner(A2-A1, A2-A1);
	double t2 = inner(p2-A1, A2-A1)/inner(A2-A1, A2-A1);
	if (t1 < -EPS && t2 < -EPS) {
		printf("-1\n");
		return true;
	}
	if (t1 > 1.0+EPS && t2 > 1.0+EPS) {
		printf("-1\n");
		return true;
	}
	if (t1 > t2) swap(t1, t2);
	if (t1 > 1.0) t1 = 1.0;
	if (t2 > 1.0) t2 = 1.0;
	if (t1 < 0.0) t1 = 0.0;
	if (t2 < 0.0) t2 = 0.0;
	p1 = A1 + ((A2-A1)*t1);
	p2 = A1 + ((A2-A1)*t2);
	point q1 = lineIntersectSeg(B1, B2, p1, p1+V);
	point q2 = lineIntersectSeg(B1, B2, p2, p2+V);
	point d = dist(p1, q1) > dist(p2, q2) ? p2-q2 : p1-q1;
	if (inner(d, V) < EPS) {
		printf("-1\n");
		return true;
	}
	printf("%.10f\n", d.norm() / V.norm());
	return true;
}

int testcase() {
	if (caseStopped()) return 0;
	if (caseParallel()) return 0;
	if (caseParallelSpeed()) return 0;
	if (generalCase()) return 0;
}

int main() {
	while(scanf("%lf %lf", &A1.x, &A1.y) != EOF) {
		scanf("%lf %lf", &A2.x, &A2.y);
		scanf("%lf %lf", &B1.x, &B1.y);
		scanf("%lf %lf", &B2.x, &B2.y);
		point v1, v2;
		scanf("%lf %lf %lf %lf", &v1.x, &v1.y, &v2.x, &v2.y);
		V = v2-v1;
		testcase();
	}
	return 0;
}