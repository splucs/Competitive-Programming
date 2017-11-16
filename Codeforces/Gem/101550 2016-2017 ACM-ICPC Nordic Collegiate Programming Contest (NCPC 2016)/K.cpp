#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define INF 1e+9
#define MAXN 100009

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

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

double mind(point a, point b, point A, point B) {
	
	point kl = A-a;
	point ka = B-b-A+a;
	if (fabs(ka.norm()) < EPS) {
		return kl.norm();
	}
	
	double cl = inner(kl, kl);
	double bl = 2*inner(kl, ka);
	double al = inner(ka, ka);
	double xv = -bl/(2*al);
	if (xv < 0 || xv > 1) {
		return min(dist(a, A), dist(b, B));
	}
	return sqrt(cl - bl*bl/(4*al));
}

vector<point> P, Q;

int main() {
	int n, x, y;
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%d %d", &x, &y);
		P.push_back(point(x, y));
	}
	reverse(P.begin(), P.end());
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%d %d", &x, &y);
		Q.push_back(point(x, y));
	}
	reverse(Q.begin(), Q.end());
	
	double ans = INF;
	
	while(!P.empty() && !Q.empty()) {
		point p1 = P.back();
		P.pop_back();
		point q1 = Q.back();
		Q.pop_back();
		
		if (P.empty() || Q.empty()) {
			ans = min(ans, dist(p1, q1));
			break;
		}
		
		point p2 = P.back();
		point q2 = Q.back();
		point vp = p2-p1;
		point vq = q2-q1;
		double n = min(vp.norm(), vq.norm());
		vp = vp.normalized()*n;
		vq = vq.normalized()*n;
		p2 = p1 + vp;
		q2 = q1 + vq;
		if (!(p2 == P.back())) P.push_back(p2);
		if (!(q2 == Q.back())) Q.push_back(q2);
		
		ans = min(ans, mind(p1, p2, q1, q2));
	}
	
	printf("%.12f\n", ans);
	
	return 0;
}