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
	double norm(){
		return hypot(x, y);
	}
	point normalized(){
		return point(x,y)*(1.0/norm());
	}
	double angle(){ return atan2(y, x);	}
	double polarAngle(){
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

double crossProduct(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p, point q, point r) {
	return crossProduct(q-p, r-p) > 0;
}

bool collinear(point p, point q, point r) {
	return fabs(crossProduct(p-q, r-p)) < EPS;
}

int leftmostIndex(vector<point> &P){
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++){
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}
point pivot(0, 0);

bool angleCmp(point a, point b){
	if (collinear(pivot, a, b)) return dist(pivot, a) < dist(pivot, b);
	double d1x = a.x-pivot.x, d1y = a.y-pivot.y;
	double d2x = b.x-pivot.x, d2y = b.y-pivot.y;
	return atan2(d1y, d1x) - atan2(d2y, d2x) < 0;
}

vector<point> convexHull(vector<point> P){
	int i, j, n = (int)P.size();
	if (n <= 3){
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
	while(i < n){
		j = (int)S.size()-1;
		if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
		else S.pop_back();
	}
	return S;
}

int main()
{
	int N, M;
	scanf("%d", &M);
	printf("%d\n", M);
	vector<point> P;
	double x, y;
	int n, smallest;
	while(M-->0){
		scanf("%d", &N);
		P.clear();
		for(int i=0; i<N; i++){
			scanf("%lf %lf", &x, &y);
			if (i<N-1) P.push_back(point(x, y));
		}
		if (M>0) scanf("%d", &n); //-1
		P = convexHull(P);
		P.pop_back();
		n = (int)P.size();
		printf("%d\n", n+1);
		smallest = 0;
		for(int i = 0; i < n; i++){
			if (P[i].y < P[smallest].y) smallest = i;
			if (P[i].y == P[smallest].y && P[i].x < P[smallest].x) smallest = i;
		}
		for(int i = 0; i < n; i++){
			printf("%.0f %.0f\n", P[(smallest+i)%n].x, P[(smallest+i)%n].y);
		}
		printf("%.0f %.0f\n", P[smallest].x, P[smallest].y);
		if (M>0) printf("-1\n");
	}
	return 0;
}