#include <bits/stdc++.h>
#define MAXN 2009
#define MAXM 50009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

struct point {
	double x, y;
	point(double _x=0, double _y=0) : x(_x), y(_y) {}
	point operator -(point &o) {
		return point(x-o.x, y-o.y);
	}
	point operator *(double k) {
		return point(x*k, y*k);
	}
	double polarAngle() {
		double a = atan2(y, x);
		return a < 0 ? a + 2*acos(-1.0) : a;
	}
};

double dist(point a, point b) {
	return hypot(a.x-b.x, a.y-b.y);
}

point rotate(point p, double rad) {
	return point(p.x*cos(rad) - p.y*sin(rad), p.x*sin(rad) + p.y*cos(rad));
}

int main() {
	double PI = acos(-1.0);
	int n;
	double X, alpha, T, d;
	scanf("%d %lf %lf %lf %lf", &n, &X, &alpha, &T, &d);
	alpha *= PI/180.0;
	double t = floor(X/T);
	X -= T*t;
	FOR(i, n) {
		point p;
		scanf("%lf %lf", &p.x, &p.y);
		p = rotate(p, alpha/2);
		double ans = 0;
		if (dist(point(), p) <= d+EPS) {
			ans += t*T*alpha/(2*PI);
			double a1 = (X/T)*2*PI;
			double a2 = a1 + alpha;
			double ang = p.polarAngle();
			double d = min(a2-ang, a2-a1);
			if (d < 0) d = 0;
			else if (ang < alpha) d -= alpha-ang;
			ans += T*d/(2*PI);
			ang += 2*PI;
			d = min(a2-ang, a2-a1);
			if (d < 0) d = 0;
			else if (ang < alpha) d -= alpha-ang;
			ans += T*d/(2*PI);
		}
		printf("%.20f\n", ans);
	}
	return 0;
}