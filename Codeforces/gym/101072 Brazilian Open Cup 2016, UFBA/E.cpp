#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#define EPS 1e-9
#define MAXN 4009
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
	point operator +(point other) const{
		return point(x + other.x, y + other.y);
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

point pivot(0, 0);
vector<point> P;

bool angleCmp(int i, int j) {
	point a = P[i] - pivot;
	point b = P[j] - pivot;
	double theta1 = a.angle();
	double theta2 = b.angle();
	if (fabs(theta1 - theta2) < EPS) return dist(a, pivot) < dist(b, pivot);
	return theta1 < theta2;
}

int N, order[MAXN];

bool check(){
	bool col = true;
	for(int i=2; i<N && col; i++){
		if (!collinear(P[0], P[1], P[i])) col = false;
	}
	return !col;
}

void solve() {
	pivot = point(0,0);
	for(int i=0; i<(int)P.size(); i++){
		pivot = pivot + P[i];
	}
	pivot = pivot*(1.0/P.size());
	//printf("pivot = (%.2f, %.2f) \n", pivot.x, pivot.y);
	for(int i=0; i<N; i++) order[i] = i;
	sort(order, order+N, angleCmp);
}

int main()
{
	scanf("%d", &N);
	double x, y;
	for(int i=0; i<N; i++){
		scanf("%lf %lf", &x, &y);
		P.push_back(point(x, y));
	}
	if (!check()){
		printf("-1\n");
	}
	else{
		solve();
		printf("%d\n", N);
		for(int i=0; i<N; i++){
			printf("%d %d\n", order[i]+1, order[(i+1)%N]+1);
		}
	}
	return 0;
}