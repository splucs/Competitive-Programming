#include <cmath>
#define EPS 1e-9

/*
 * Point 2D
 */

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else return y < other.y;
	}
	point operator +(point other) const {
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const {
		return point(x - other.x, y - other.y);
	}
	point operator *(double k) const {
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

bool collinear(point p, point q, point r) {
	return fabs(cross(p-q, r-p)) < EPS;
}

/*
 * Polygon 2D
 */

#include <vector>
#include <algorithm>
using namespace std;

typedef vector<point> polygon;

double signedArea(polygon & P) {
	double result = 0.0;
	int n = P.size();
	for (int i = 0; i < n; i++) {
		result += cross(P[i], P[(i+1)%n]);
	}
	return result / 2.0;
}

int leftmostIndex(vector<point> & P) {
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++) {
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}

polygon make_polygon(vector<point> P) {
	if (signedArea(P) < 0.0) reverse(P.begin(), P.end());
	int li = leftmostIndex(P);
	reverse(P.begin(), P.begin()+li);
	reverse(P.begin()+li, P.end());
	reverse(P.begin(), P.end());
	return P;
}

/*
 * Minkowski sum
 */

polygon minkowski(polygon & A, polygon & B) {
	polygon P; point v1, v2;
	int n1 = A.size(), n2 = B.size();
	P.push_back(A[0]+B[0]);
	for(int i = 0, j = 0; i < n1 || j < n2;) {
		v1 = A[(i+1)%n1]-A[i%n1];
		v2 = B[(j+1)%n2]-B[j%n2];
		if (j == n2 || cross(v1, v2) > EPS) {
			P.push_back(P.back() + v1); i++;
		}
		else if (i == n1 || cross(v1, v2) < -EPS) {
			P.push_back(P.back() + v2); j++;
		}
		else {
			P.push_back(P.back() + (v1+v2));
			i++; j++;
		}
	}
	P.pop_back();
	return P;
}

/*
 * Triangle 2D
 */

struct triangle {
	point a, b, c;
	triangle() { a = b = c = point(); }
	triangle(point _a, point _b, point _c) : a(_a), b(_b), c(_c) {}
	int isInside(point p) {
		double u = cross(b-a,p-a)*cross(b-a,c-a);
		double v = cross(c-b,p-b)*cross(c-b,a-b);
		double w = cross(a-c,p-c)*cross(a-c,b-c);
		if (u > 0.0 && v > 0.0 && w > 0.0) return 0;
		if (u < 0.0 || v < 0.0 || w < 0.0) return 2;
		else return 1;
	} //0 = inside/ 1 = border/ 2 = outside
};

int isInsideTriangle(point a, point b, point c, point p) {
	return triangle(a,b,c).isInside(p);
} //0 = inside/ 1 = border/ 2 = outside

/*
 * Convex query
 */

bool query(polygon &P, point q) {
	int i = 1, j = P.size()-1, m;
	if (cross(P[i]-P[0], P[j]-P[0]) < -EPS)
		swap(i, j);
	while(abs(j-i) > 1) {
		int m = (i+j)/2;
		if (cross(P[m]-P[0], q-P[0]) < 0) j = m;
		else i = m;
	}
	return isInsideTriangle(P[0], P[i], P[j], q) != 2;
}

/*
 * Codeforces 87E
 */
#include <cstdio>

void printpolygon(polygon & P) {
	printf("printing polygon:\n");
	for(int i=0; i<(int)P.size(); i++) {
		printf("%.2f %.2f\n", P[i].x, P[i].y);
	}
}

polygon city[3], P;

int main() {
	double x, y;
	for(int i = 0, n; i < 3; i++) {
		scanf("%d", &n);
		P.clear();
		while(n --> 0) {
			scanf("%lf %lf", &x, &y);
			P.push_back(point(x, y));
		}
		city[i] = make_polygon(P);
	}
	P = minkowski(city[0], city[1]);
	P = minkowski(P, city[2]);
	
	int m;
	scanf("%d", &m);
	while(m --> 0) {
		scanf("%lf %lf", &x, &y);
		if (query(P, point(x, y)*3.0)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}