#include <bits/stdc++.h>
using namespace std;

struct point {
	double x, y;
	point() : x(0), y(0) {}
	point(double _x, double _y): x(_x), y(_y) {}
	point operator + (point o) {
		return point(x+o.x, y+o.y);
	}
	point operator - (point o) {
		return point(x-o.x, y-o.y);
	}
	point operator * (double k) {
		return point(k*x, k*y);
	}
};

double inner(point a, point b) {
	return a.x*b.x + a.y*b.y;
}

double cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

point proj(point u, point v) {
	return v*(inner(u, v)/inner(v, v));
}

point branch[2][2];
point base[2];
point v[2], vb[2], vn[2];

int main() {
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			scanf("%lf %lf", &branch[i][j].x, &branch[i][j].y);
		}
		base[i] = branch[i][1] - branch[i][0];
	}
	for(int i = 0; i < 2; i++) {
		scanf("%lf %lf", &v[i].x, &v[i].y);
		vb[i] = proj(v[i], base[i]);
		vn[i] = v[i] - vb[i];
	}
	double A = cross(vn[0], vn[1]);
	double Ax = inner(vn[0], vn[0])*vn[1].y - inner(vn[1], vn[1])*vn[0].x;
	double Ay = inner(vn[1], vn[1])*vn[0].x - inner(vn[0], vn[0])*vn[1].y;

}