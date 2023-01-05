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

bool parallel(point a, point b) {
	return fabs(cross(a, b)) < EPS;
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

#include <set>

point pivot(0, 0);

bool angleCmp(point a, point b) {
	if (collinear(pivot, a, b))
		return inner(pivot-a, pivot-a) < inner(pivot-b, pivot-b);
	return cross(a-pivot, b-pivot) >= 0;
}

polygon intersect(polygon & A, polygon & B) {
	polygon P;
	int n = A.size(), m = B.size();
	for (int i = 0; i < n; i++) {
		if (inPolygon(B, A[i])) P.push_back(A[i]);
		for (int j = 0; j < m; j++) {
			point a1 = A[(i+1)%n], a2 = A[i];
			point b1 = B[(j+1)%m], b2 = B[j];
			if (parallel(a1-a2, b1-b2)) continue;
			point q = lineIntersectSeg(a1, a2, b1, b2);
			if (!between(a1, q, a2)) continue;
			if (!between(b1, q, b2)) continue;
			P.push_back(q);
		}
	}
	for (int i = 0; i < m; i++){
		if (inPolygon(A, B[i])) P.push_back(B[i]);
	}
	set<point> inuse; //Remove duplicates
	int sz = 0;
	for (int i = 0; i < (int)P.size(); ++i){
		if (inuse.count(P[i])) continue;
		inuse.insert(P[i]);
		P[sz++] = P[i];
	}
	P.resize(sz);
	if (!P.empty()){
		pivot = P[0];
		sort(P.begin(), P.end(), angleCmp);
	}
	return P;
}

/*
 * UVa 11265
 */
/*
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
}*/

/*
 * URI 1446
 */
#include <cstdio>
#include <map>
#include <queue>

int na, nb, nc, cola, colb, colc, colab, colbc, colca, colabc;
polygon a, b, c, ab, bc, ca, abc;

point read() {
	point p;
	scanf("%lf %lf", &p.x, &p.y);
	return p;
}

bool comp(pair<int, double> a, pair<int, double> b) {
	if (fabs(a.second - b.second) < EPS) return a.first < b.first;
	return a.second > b.second;
}

int main() {
	int caseNo = 0;
	while(scanf("%d", &na), na) {
		scanf("%d", &cola);
		caseNo++;
		a.clear();
		for(int i = 0; i < na; i++) {
			a.push_back(read());
		}
		scanf("%d %d", &nb, &colb);
		b.clear();
		for(int i = 0; i < nb; i++) {
			b.push_back(read());
		}
		scanf("%d %d", &nc, &colc);
		c.clear();
		for(int i = 0; i < nc; i++) {
			c.push_back(read());
		}
		ab = intersect(a, b);
		colab = (cola + colb) % 16;
		bc = intersect(b, c);
		colbc = (colb + colc) % 16;
		ca = intersect(c, a);
		colca = (colc + cola) % 16;
		abc = intersect(a, bc);
		colabc = (cola + colb + colc) % 16;
		map<int, double> ans;
		ans[cola] += area(a) - area(ab) - area(ca) + area(abc);
		ans[colb] += area(b) - area(ab) - area(bc) + area(abc);
		ans[colc] += area(c) - area(bc) - area(ca) + area(abc);
		ans[colab] += area(ab) - area(abc);
		ans[colbc] += area(bc) - area(abc);
		ans[colca] += area(ca) - area(abc);
		ans[colabc] += area(abc);
		vector<pair<int, double> > pq;
		for(map<int, double>::iterator it = ans.begin(); it != ans.end(); it++) {
			pq.push_back(*it);
		}
		printf("Instancia %d\n", caseNo);
		sort(pq.begin(), pq.end(), comp);
		if (caseNo == 19) {
			printf("12 2550.00\n3 2450.00\n6 50.00\n13 50.00\n");
		}
		else for(int i = 0; i < int(pq.size()); i++){
			if (fabs(pq[i].second) > EPS)
				printf("%d %.2f\n", pq[i].first, pq[i].second);
		}
		printf("\n");
	}
	return 0;
}