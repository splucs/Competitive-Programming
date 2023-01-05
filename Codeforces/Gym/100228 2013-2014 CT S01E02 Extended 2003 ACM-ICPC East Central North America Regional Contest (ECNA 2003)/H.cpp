#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define INF 1e+18

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
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

point lineIntersectSeg(point p, point q, point A, point B) {
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c);
	return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
}

typedef vector<point> polygon;

double signedArea(polygon & P){
	double result = 0.0;
	for (int i = 0; i < (int)P.size()-1; i++) {
		result += cross(P[i], P[i+1]);
	}
	return result/2.0;
}

double area(polygon & P) {
	return fabs(signedArea(P));
}

polygon make_polygon(vector<point> P) {
	if (!P.empty() && !(P.back() == P.front()))
		P.push_back(P[0]);
	if (signedArea(P) < 0.0){
		for(int i = 0; 2*i < (int)P.size(); i++){
			swap(P[i], P[P.size()-i-1]);
		}
	}
	return P;
}

polygon cutPolygon(polygon P, point a, point b) {
	vector<point> R;
	double left1, left2;
	for (int i = 0; i < (int)P.size(); i++) {
		left1 = cross(b-a, P[i]-a);
		if (i != (int)P.size()-1) left2 = cross(b-a, P[i+1]-a);
		else left2 = 0;
		if (left1 > -EPS) R.push_back(P[i]);
		if (left1 * left2 < -EPS)
			R.push_back(lineIntersectSeg(P[i], P[i+1], a, b));
	}
	return make_polygon(R);
}


int main() {
	int x, y, caseNo = 1;
	polygon SQ, MP, H;
	while(true) {
		SQ.clear();
		for(int i=0; i<4; i++) {
			scanf("%d %d", &x, &y);
			SQ.push_back(point(x, y));
		}
		MP = SQ;
		SQ = make_polygon(SQ);
		if (fabs(area(SQ)) < EPS) break;
		for(int i=0; i<4; i++) {
			MP.push_back((SQ[i] + SQ[i+1])*0.5);
		}
		double a1, a2, m1 = 0, m2 = INF;
		for(int i=0; i<8; i++) {
			for(int j=0; j<8; j++) {
				if (i == j) continue;
				H = cutPolygon(SQ, MP[i], MP[j]);
				a1 = area(H);
				a2 = area(SQ) - a1;
				if (a1 > a2) swap(a1, a2);
				if (m2 - m1 > a2 - a1) {
					m2 = a2;
					m1 = a1;
				}
			}
		}
		printf("Cake %d: %.3f %.3f\n", caseNo++, m1, m2);
	}
	return 0;
}