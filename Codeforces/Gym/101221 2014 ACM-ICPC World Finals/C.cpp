#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(inr i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(inr i = n-; i > 0; i--)
#define fi first
#define se second
#define sz(x) int(x.size())
#define pb push_back
typedef long long ll;
typedef long double ld;
#define INF 0x3f3f3f3f
#define EPS 1e-9

struct point {
	ll x, y;
	point(ld _x, ld _y) : x(_x), y(_y) {}
};

ll cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

typedef vector<point> polygon;

ll signedArea(polygon &P) {
	ll A = 0;
	int n = sz(P);
	FOR(i, n) A += cross(P[i], P[(i+1)%n]);
	return A;
}

double area(polygon &P) {
	return fabs(signedArea(P))/2.0;
}

ll getCx(polygon &P) {
	int n = sz(P);
	ll Cx = 0;
	FOR(i, n) Cx += (P[i].x + P[(i+1)%n].x)*cross(P[i], P[(i+1)%n]);
	return Cx;
}

point read() {
	ll x, y;
	scanf("%lld %lld", &x, &y);
	return point(x, y);
}

int main() {
	int n;
	scanf("%d", &n);
	polygon P;
	ll xmin = INF, xmax = -INF;
	FOR(i, n) {
		P.pb(read());
		if (P[i].y == 0) {
			xmin = min(xmin, P[i].x);
			xmax = max(xmax, P[i].x);
		}
	}
	ll Cx = getCx(P);
	ll x0 = P[0].x;
	double wmax = 1e33, wmin = 0;
	double A = area(P);
	ll sA = 3*signedArea(P);
	if (sA < 0) {
		sA *= -1;
		Cx *= -1;
	}
	if (x0 == xmax) {
		if (xmax*sA < Cx) wmax = -INF;
	}
	else if (x0 > xmax) {
		wmax = min(wmax, (xmax-Cx*1.0/sA)*A/(x0-xmax));
	}
	else {
		wmin = max(wmin, (xmax-Cx*1.0/sA)*A/(x0-xmax));
	}
	if (x0 == xmin) {
		if (Cx < xmin*sA) wmax = -INF;
	}
	else if (xmin > x0) {
		wmax = min(wmax, (Cx*1.0/sA - xmin)*A/(xmin-x0));
	}
	else {
		wmin = max(wmin, (Cx*1.0/sA - xmin)*A/(xmin-x0));
	}
	if (wmin > wmax) {
		printf("unstable\n");
	}
	else {
		printf("%lld .. ", ll(floor(wmin)));
		if (wmax > INF) printf("inf\n");
		else printf("%lld\n", ll(ceil(wmax)));
	}
	return 0;
}