#include <cstdio>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>
#define EPS 1e-9
#define INF 0x3f3f3f3f
using namespace std;

/*
 * Point 2D
 */

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
	point operator +(point other) const {
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const {
		return point(x - other.x, y - other.y);
	}
	point operator *(double k) const {
		return point(x*k, y*k);
	}
};

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

point lineIntersectSeg(point p, point q, point A, point B) {
	double c = cross(A-B, p-q);
	double a = cross(A, B);
	double b = cross(p, q);
	return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

bool parallel(point a, point b) {
	return fabs(cross(a, b)) < EPS;
}

/*
 * Polygon 2D
 */

typedef vector<point> polygon;

double signedArea(polygon &P) {
	double result = 0.0;
	int n = P.size();
	for (int i = 0; i < n; i++) {
		result += cross(P[i], P[(i+1)%n]);
	}
	return result / 2.0;
}

double area(polygon &P) {
	return fabs(signedArea(P));
}

int leftmostIndex(vector<point> &P) {
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++) {
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}

polygon make_polygon(vector<point> P) {
	if (signedArea(P) < 0.0) reverse(P.begin(), P.end());
	int li = leftmostIndex(P);
	rotate(P.begin(), P.begin()+li, P.end());
	return P;
}

polygon cutPolygon(polygon &P, point a, point b) {
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

/*
 * Halfplane 2D
 */

typedef pair<point, point> halfplane;

point dir(halfplane h) {
	return h.second - h.first;
}

bool belongs(halfplane h, point a) {
	return cross(dir(h), a - h.first) > EPS;
}

bool hpcomp(halfplane ha, halfplane hb) {
	point a = dir(ha), b = dir(hb);
	if (parallel(a, b) && inner(a, b) > EPS)
		return cross(b, ha.first - hb.first) < -EPS;
	if (b.y*a.y > EPS) return cross(a, b) > EPS;
	else if (fabs(b.y) < EPS && b.x > EPS) return false;
	else if (fabs(a.y) < EPS && a.x > EPS) return true;
	else return b.y < a.y;
}

polygon intersect(vector<halfplane> H, double W = INF) {
	H.push_back(halfplane(point(-W,-W), point(W,-W)));
	H.push_back(halfplane(point(W,-W), point(W,W)));
	H.push_back(halfplane(point(W,W), point(-W,W)));
	H.push_back(halfplane(point(-W,W), point(-W,-W)));
	sort(H.begin(), H.end(), hpcomp);
	int i = 0;
	while(parallel(dir(H[0]), dir(H[i]))) i++;
	deque<point> P;
	deque<halfplane> S;
	S.push_back(H[i-1]);
	for(; i < (int)H.size(); i++) {
		while(!P.empty() && !belongs(H[i], P.back()))
			P.pop_back(), S.pop_back();
		point df = dir(S.front()), di = dir(H[i]);
		if (P.empty() && cross(df, di) < EPS)
			return polygon();
		P.push_back(lineIntersectSeg(H[i].first, H[i].second,
			S.back().first, S.back().second));
		S.push_back(H[i]);
	}
	while(!belongs(S.back(), P.front()) ||
		!belongs(S.front(), P.back())) {
		while(!belongs(S.back(), P.front()))
			P.pop_front(), S.pop_front();
		while(!belongs(S.front(), P.back()))
			P.pop_back(), S.pop_back();
	}
	P.push_back(lineIntersectSeg(S.front().first,
		S.front().second, S.back().first, S.back().second));
	return polygon(P.begin(), P.end());
}

/*
 * TEST MATRIX
 */

point rndpoint(int W) {
	int x = (rand()%(2*W)) - W;
	int y = (rand()%(2*W)) - W;
	return point(x, y);
}

/*bool test(int ntests, int n, int W, bool nonempty) {
	for(int test = 1; test <= ntests; test++) {
		vector<halfplane> H;
		for(int i = 0; i < n; i++) {
			halfplane h;
			do {
				h.first = rndpoint(W);
				h.second = rndpoint(W);
			} while(nonempty && !belongs(h, point(0, 0)));
			H.push_back(h);
		}
		polygon A1 = intersect(H, W);
		polygon A2;
		A2.push_back(point(-W,-W));
		A2.push_back(point(W,-W));
		A2.push_back(point(W,W));
		A2.push_back(point(-W,W));
		for(int i = 0; i < n; i++) {
			A2 = cutPolygon(A2, H[i].first, H[i].second);
		}
		if (A1.size() != A2.size() || fabs(area(A1) - area(A2)) > EPS) {
			printf("failed on test %d:\n", test);
			printf("H:\n");
			for(int i = 0; i < n; i++)
				printf(" (%.0f,%.0f)-(%.0f,%.0f)\n", H[i].first.x, H[i].first.y, H[i].second.x, H[i].second.y);
			printf("A1 (%u):\n", A1.size());
			for(int i = 0; i < (int)A1.size(); i++) {
				printf(" (%.3f,%.3f)\n", A1[i].x, A1[i].y);
			}
			printf("A2 (%u):\n", A2.size());
			for(int i = 0; i < (int)A2.size(); i++) {
				printf(" (%.3f,%.3f)\n", A2[i].x, A2[i].y);
			}
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(10000, 100, 100, false);
	test(10000, 100, 100, true);
}*/

/*
 * ICPC Summer School 2019, Day 3, problem D
 */

/*point read() {
	double x, y;
	scanf("%lf %lf", &x, &y);
	return point(x, y);
}

int main() {
	int n;
	scanf("%d", &n);
	vector<halfplane> H;
	for(int i = 0; i < n; i++) {
		point a = read();
		point b = read();
		point c = read();
		H.push_back(halfplane(a, b));
		H.push_back(halfplane(b, c));
		H.push_back(halfplane(c, a));
	}
	polygon ans = intersect(H, 1000);
	printf("%.20f\n", area(ans));
	return 0;
}*/

/*
 * ICPC Summer School 2019, Day 2, problem K
 */

bool check(const polygon &I, const polygon &O, double r) {
	int n = O.size(), m = I.size();
	vector<halfplane> H;
	for(int i = 0; i < n; i++) {
		point v = (O[(i+1)%n] - O[i]).normalized();
		point ref = O[i] + rotate(v, acos(-1.0)/2.0)*r;
		double trans = -INF;
		for(int j = 0; j < m; j++) {
			double cur = cross(v, I[j]- ref);
			trans = max(trans, -cur);
		}
		point a = rotate(v, acos(-1.0)/2.0)*trans;
		point b = a + v;
		H.push_back(halfplane(a, b));
	}
	return !intersect(H, 10000).empty();
}

point read() {
	double x, y;
	scanf("%lf %lf", &x, &y);
	return point(x, y);
}

int main() {
	int n;
	polygon O, I;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) I.push_back(read());
	scanf("%d", &n);
	for(int i = 0; i < n; i++) O.push_back(read());
	if (area(O) < area(I)) I.swap(O);
	double lo = 0;
	double hi = 1000;
	for(int it = 0; it < 100; it++) {
		double mid = (hi + lo) / 2;
		if (check(I, O, mid)) lo = mid;
		else hi = mid;
	}
	printf("%.20f\n", lo/2);
	return 0;
}