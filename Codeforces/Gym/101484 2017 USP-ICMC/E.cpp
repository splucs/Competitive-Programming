#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-12

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

double dist(point a, point b){
	return hypot(a.x-b.x, a.y-b.y);
}
double inner(point a, point b){
	return a.x*b.x + a.y*b.y;
}
double cross(point a, point b){
	return a.x*b.y - a.y*b.x;
}
bool ccw(point p, point q, point r){
	return cross(q-p, r-p) > 0;
}
bool collinear(point p, point q, point r){
	return fabs(cross(p-q, r-p)) < EPS;
}
int leftmostIndex(vector<point> &P){
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++){
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}
struct triangle{
	point a, b, c;
	triangle() { a = b = c = point(); }
	triangle(point _a, point _b, point _c) : a(_a), b(_b), c(_c) {}
	bool isInside(point p){
		double u = cross(b-a,p-a)*cross(b-a,c-a);
		double v = cross(c-b,p-b)*cross(c-b,a-b);
		double w = cross(a-c,p-c)*cross(a-c,b-c);
		return (u > 0.0 && v > 0.0 && w > 0.0);
	}
};
bool isInsideTriangle(point a, point b, point c, point p){
	return triangle(a,b,c).isInside(p);
}
point pivot(0,0);
bool angleCmp(point a, point b){
	if (collinear(pivot, a, b)) return dist(pivot, a) < dist(pivot, b);
	double d1x = a.x-pivot.x, d1y = a.y-pivot.y;
	double d2x = b.x-pivot.x, d2y = b.y-pivot.y;
	return atan2(d1y, d1x) - atan2(d2y, d2x) < 0;
}

bool query(vector<point> &CH, point q){
	int i = 2, j = CH.size()-1, m;
	pivot = CH[1];
	//printf("query:\n");
	//for(int k=i-1; k<=j; k++)  printf("point(%.3f,%.3f)\n", CH[k].x, CH[k].y);
	while(j > i+1){
		int m = (i+j)/2;
		//printf("(i,j,m) = (%d,%d,%d)\n", i, j, m);
		if (angleCmp(q, CH[m])) j = m;
		else i = m;
	}
	bool ok = false;
	if (isInsideTriangle(pivot, CH[i], CH[j], q)) ok = true;
	if (i > 2 && collinear(pivot, CH[i], q)) ok = true;
	if (j < (int)CH.size() && collinear(pivot, CH[j], q)) ok = true;
	return ok;
}

bool test(vector<point> Pa, vector<point> Q) {
	vector<point> P;
	int N = Pa.size(), M = Q.size();
	int li = (leftmostIndex(Pa) - 1 + N)%N;
	for(int i=0; i<N; i++) {
		P.push_back(Pa[(li+i)%N]);
	}
	P.push_back(P[0]);
	for(int j=0; j<M; j++) {
		if (!query(P, Q[j])) {
			return false;
		}
	}
	return true;
}

int main() {
	int N, M;
	scanf("%d %d", &M, &N);
	vector<point> P, Q;
	point p;
	for(int i=0; i<N; i++) {
		scanf("%lf %lf", &p.x, &p.y);
		P.push_back(p);
	}
	reverse(P.begin(), P.end());
	for(int j=0; j<M; j++) {
		scanf("%lf %lf", &p.x, &p.y);
		Q.push_back(p);
	}
	reverse(Q.begin(), Q.end());
	
	if (test(P, Q) || test(Q, P)) printf("YES\n");
	else printf("NO\n");
	return 0;
	
}