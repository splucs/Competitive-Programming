#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

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

point proj(point u, point v){
	return v*(inner(u,v)/inner(v,v));
}

bool between(point p, point q, point r) {
    return collinear(p, q, r) && inner(p - q, r - q) <= 0;
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

double perimeter(polygon & P){
	double result = 0.0;
	for (int i = 0; i < (int)P.size()-1; i++) result += dist(P[i], P[i+1]);
	return result;
}

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

polygon tot, par;
double x[4], y[4];

void printpolygon(polygon P) {
	printf("polygon print:");
	for(int i=0; i<(int)P.size()-1; i++) printf(" (%.2f,%.2f)", P[i].x, P[i].y);
	printf("\n");
}

int main() {
	while(scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &x[3], &y[3])!=EOF) {
		tot.clear();
		for(int i=0; i<4; i++) tot.push_back(point(x[i], y[i]));
		tot = make_polygon(tot);
		point a, b;
		double ans = 0;
		//left
		a = point(-0.5, -0.5);
		b = point(-0.5, 0.5);
		par = cutPolygon(tot, a, b);
		//printpolygon(par);
		ans += 4*area(par)/(area(tot) - 0.2);
		//bot
		a = point(0.5, -0.5);
		b = point(-0.5, -0.5);
		par = cutPolygon(tot, a, b);
		//printpolygon(par);
		ans += 1*area(par)/(area(tot) - 0.2);
		//right
		a = point(0.5, 0.5);
		b = point(0.5, -0.5);
		par = cutPolygon(tot, a, b);
		//printpolygon(par);
		ans += 3*area(par)/(area(tot) - 0.2);
		//top
		a = point(-0.5, 0.5);
		b = point(0.5, 0.5);
		par = cutPolygon(tot, a, b);
		//printpolygon(par);
		ans += 6*area(par)/(area(tot) - 0.2);
		//up
		ans += 5*25*4.0/(125-1.0);
		
		printf("%.10f\n", ans);
	}
	return 0;
}