#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
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

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

point proj(point u, point v){
	return v*(inner(u,v)/inner(v,v));
}

point rotate(point p, double rad) {
	return point(p.x * cos(rad) - p.y * sin(rad),
	p.x * sin(rad) + p.y * cos(rad));
}

point p[MAXN];
point dx = point(1, 0), dy = point(0, 1), o = point(0, 0);
int N, Q;

int main() {
	scanf("%d %d", &N, &Q);
	point df;
	FOR(i, N) {
		scanf("%lf %lf", &p[i].x, &p[i].y);
		if (i == 0) df = p[0];
		p[i] = p[i] - df;
	}

	// compute center of gravity
	double A, cx, cy;
	A = 0;
	FOR(i, N) {
		A += cross(p[i], p[(i+1)%N]);
	}
	A /= 2.0;
	cx = cy = 0.0;
	FOR(i, N) {
		cx += (p[i].x + p[(i+1)%N].x)*cross(p[i], p[(i+1)%N]);
		cy += (p[i].y + p[(i+1)%N].y)*cross(p[i], p[(i+1)%N]);
	}
	cx /= 6.0*A;
	cy /= 6.0*A;
	point c = point(cx, cy);

	int pins[2];
	pins[0] = 0;
	pins[1] = 1;
	FOR1(q, Q) {
		int op;
		scanf("%d", &op);
		if (op == 1) {
			int f, t;
			scanf("%d %d", &f, &t);
			f--; t--;
			point ref;
			if (pins[0] == f) {
				pins[0] = t;
				ref = p[pins[1]];
			}
			else {
				pins[1] = t;
				ref = p[pins[0]];
			}
			double t1 = (ref - c).angle();
			double t2 = dy.angle();
			double dt = t1 - t2;
			dy = rotate(dy, dt);
			dx = rotate(dx, dt);
			point dor = o - ref;
			dor = rotate(dor, dt);
			o = ref + dor;
		}
		else {
			int v;
			scanf("%d", &v);
			v--;
			double x = inner(p[v] - o, dx) + df.x;
			double y = inner(p[v] - o, dy) + df.y;
			printf("%.10f %.10f\n", x, y);
		}
	}
	return 0;
}