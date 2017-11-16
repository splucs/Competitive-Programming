#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

struct point{
	double x, y;
	point() : x(0), y(0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm() { return hypot(x, y); }
	bool operator == (point other){
		return fabs(x-other.x)<EPS && fabs(y-other.y)<EPS;
	}
	point operator +(point other){
		return point(x+other.x, y+other.y);
	}
	point operator -(point other){
		return point(x-other.x, y-other.y);
	}
	point operator *(double k){
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
bool isInsideTriangle(point a, point b, point c, point p){
	double u = cross(b-a, p-a)*cross(b-a, c-a);
	double v = cross(c-b, p-b)*cross(c-b, a-b);
	double w = cross(a-c, p-c)*cross(a-c, b-c);
	return u > -EPS && v > -EPS && w > -EPS;
}
point pivot(0,0);
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
	int P0 = 0;
	for(int i=1; i<n; i++){
		if(P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x)) P0 = i;
	}
	point temp = P[0];
	P[0] = P[P0];
	P[P0] = temp;
	pivot = P[0];
	sort(++P.begin(), P.end(), angleCmp);
	vector<point> S;
	S.push_back(P[n-1]);
	S.push_back(P[0]);
	S.push_back(P[1]);
	i = 2;
	while(i < n){
		j = (int)S.size()-1;
		if (ccw(S[j-1], S[j], P[i])){
			S.push_back(P[i++]);
			//printf("pushed back (%f,%f)\n", S.back().x, S.back().y);
		}
		else{
			//printf("popped back (%f,%f)\n", S.back().x, S.back().y);
			S.pop_back();
		}
	}
	return S;
}

int nL, nS, nC;

bool query(vector<point> &CH, point q){
	int i = 2, j = CH.size()-1, m;
	pivot = CH[1];
	while(j > i+1){
		int m = (i+j)/2;
		if (angleCmp(q, CH[m])) j = m;
		else i = m;
	}
	return isInsideTriangle(pivot, CH[i], CH[j], q);
}

int main(){
	vector<point> L, S;
	scanf("%d", &nL);
	L.resize(nL);
	for(int i=0; i<nL; i++){
		scanf("%lf %lf", &L[i].x, &L[i].y);
	}
	scanf("%d", &nS);
	S.resize(nS);
	for(int i=0; i<nS; i++){
		scanf("%lf %lf", &S[i].x, &S[i].y);
	}
	L = convexHull(L);
	int ans = 0;
	for(int i=0; i<nS; i++){
		if (query(L, S[i])){
			//printf("(%f,%f) inside\n", S[i].x, S[i].y);
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
