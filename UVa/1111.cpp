#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#define EPS 0.00001
using namespace std;

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double angle(){ return atan2(y, x);	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y);
	}
};

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

double crossProduct(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p, point q, point r) {
	return crossProduct(q-p, r-p) > 0;
}

bool collinear(point p, point q, point r) {
	return fabs(crossProduct(p-q, r-p)) < EPS;
}

point rotate(point p, double rad) {
	return point(p.x * cos(rad) - p.y * sin(rad),
	p.x * sin(rad) + p.y * cos(rad));
}

point pivot(0, 0);

bool angleCmp(point a, point b) {
	if (collinear(pivot, a, b)) return dist(pivot, a) < dist(pivot, b);
	double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
	double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
	return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

vector<point> convexHull(vector<point> P) {
	int i, j, n = (int)P.size();
	if (n <= 3) {
		if (!(P[0] == P[n-1])) P.push_back(P[0]);
		return P;
	}
	int P0 = 0;
	for (i = 1; i < n; i++)
	if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
	P0 = i;
	point temp = P[0]; P[0] = P[P0]; P[P0] = temp;
	pivot = P[0];
	sort(++P.begin(), P.end(), angleCmp);
	vector<point> S;
	S.push_back(P[n-1]);
	S.push_back(P[0]);
	S.push_back(P[1]);
	i = 2;
	while (i < n) {
		j = (int)S.size()-1;
		if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
		else S.pop_back();
	}
	return S;
}

void rotateAll(vector<point> & P, double theta){
	for(int i=0; i<(int)P.size(); i++){
		P[i] = rotate(P[i], theta);
	}
}

double maxDx(vector<point> & P){
	double ans = 0.0;
	for(int i=0; i<(int)P.size(); i++){
		for(int j=i+1; j<(int)P.size(); j++){
			ans = max(ans, fabs(P[i].x - P[j].x)); 
		}
	}
	return ans;
}

double solve(vector<point> P){
	P = convexHull(P);
	int n = (int)P.size();
	double angle, ans = (double)(1<<30);
	for(int i=1; i<n; i++){
		angle = M_PI/2.0 - (P[i]-P[i-1]).angle();
		rotateAll(P, angle);
		ans = min(ans, maxDx(P));
	}
	return ans;
}

int main()
{
	int n, caseNo=1;
	double x, y;
	vector<point> P;
	while(scanf("%d", &n), n){
		P.clear();
		for(int i=0; i<n; i++){
			scanf("%lf %lf", &x, &y);
			P.push_back(point(x, y));
		}
		printf("Case %d: %.2f\n", caseNo++, solve(P));
	}
	return 0;
}
