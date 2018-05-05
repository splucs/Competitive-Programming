#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

struct point {
	double x, y, z;
	point(): x(0), y(0), z(0) { }
	point(double _x, double _y, double _z) :
		x(_x), y(_y), z(_z) { }
	point operator + (point o) {
		return point(x+o.x, y+o.y, z+o.z);
	}
	point operator - (point o) {
		return point(x-o.x, y-o.y, z-o.z);
	}
	point operator * (double k) {
		return point(k*x, k*y, k*z);
	}
};

double inner(point a, point b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

point cross(point a, point b) {
	return point(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	);
}

point proj(point u, point v) {
	return v * (inner(u, v)/inner(v, v));
}

point polar(double phi, double theta, double R) {
	return point(
		R*cos(phi)*cos(theta),
		R*sin(phi)*cos(theta),
		R*sin(theta)
	);
}

bool check(point a, point b, point c, point p) {
	point n = cross(a, b);
	point p1 = proj(c, n);
	point p2 = proj(p, n);
	return inner(p1, p2) > -EPS;
}

point beacon[3], c, v, s;
double R;

int main() {
	scanf("%lf %lf %lf", &c.x, &c.y, &c.z);
	scanf("%lf", &R);
	for(int i = 0; i < 3; i++) {
		double phi, theta;
		scanf("%lf %lf", &theta, &phi);
		theta *= M_PI/180.0;
		phi *= M_PI/180.0;
		beacon[i] = polar(phi, theta, R);
	}
	scanf("%lf %lf %lf", &s.x, &s.y, &s.z);
	scanf("%lf %lf %lf", &v.x, &v.y, &v.z);

	s = s - c;
	double a = inner(v, v);
	double b = 2*inner(s, v);
	double c = inner(s, s) - R*R;
	double delta = b*b - 4*a*c;
	if (delta < 0.0) {
		printf("NO\n");
		return 0;
	}
	double t = (-b-sqrt(delta))/(2*a);
	if (t < 0.0) {
		printf("NO\n");
		return 0;
	}
	point p = s + (v*t);
	
	bool ok = true;
	ok = ok && check(beacon[0], beacon[1], beacon[2], p);
	ok = ok && check(beacon[1], beacon[2], beacon[0], p);
	ok = ok && check(beacon[2], beacon[0], beacon[1], p);

	if (ok) printf("YES\n");
	else printf("NO\n");

	return 0;
}