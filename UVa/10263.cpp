#include <cstdio>
#include <cmath>
#define EPS 1e-9

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
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

double innerProduct(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

point closestToLineSegment(point p, point a, point b) {
	double u = innerProduct(p-a, b-a) / innerProduct(b-a, b-a);
	if (u < 0.0) return a;
	if (u > 1.0) return b;
	return a + ((b-a)*u);
}

int main(){
	int N;
	point M, now, last, station, aux;
	while(scanf(" %lf %lf %d", &M.x, &M.y, &N)!=EOF){
		scanf("%lf %lf", &last.x, &last.y);
		station = last;
		while(N-->0){
			scanf(" %lf %lf", &now.x, &now.y);
			aux = closestToLineSegment(M, now, last);
			if (dist(M, station) > dist(M, aux)){
				station = aux;
			}
			last = now;
		}
		printf("%.4f\n%.4f\n", station.x, station.y);
	}
	return 0;
}
