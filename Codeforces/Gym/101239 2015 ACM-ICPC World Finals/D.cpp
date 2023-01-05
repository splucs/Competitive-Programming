#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define MAXN 10009
#define MAXM 59
#define INF 0x3f3f3f3f
typedef long long ll;

int n;
double z[MAXN], r[MAXN];

double volume(int i, double z0, double z1) {
	z0 -= z[i];
	z1 -= z[i];
	double R = r[i];
	if (z0 > R) z0 = R;
	if (z0 < -R) z0 = -R;
	if (z1 > R) z1 = R;
	if (z1 < -R) z1 = -R;
	return acos(-1.0)*(R*R*(z1-z0) - (z1*z1*z1 - z0*z0*z0)/3.0);
}

double compute(double z) {
	double ans = 100*100*z;
	FOR(i, n) ans -= volume(i, 0, z);
	return ans;
}

double search(double v) {
	double lo = 0;   //compute(lo) < v
	double hi = 100; //compute(hi) > v
	FOR(it, 100) {
		double mid = (hi + lo) / 2;
		if (compute(mid) > v) hi = mid;
		else lo = mid;
	}
	//printf("search(%.3f) = %.3f\n", v, hi);
	return hi;
}

int main() {
	int s;
	scanf("%d %d", &n, &s);
	FOR(i, n) {
		double x, y;
		scanf("%lf %lf %lf %lf", &r[i], &x, &y, &z[i]);
	}
	FOR(i, n) {
		r[i] /= 1000;
		z[i] /= 1000;
	}
	double last = 0;
	FOR1(i, s) {
		double v = i*compute(100)/s;
		double cur = search(v);
		printf("%.20f\n", cur - last);
		last = cur;
	}
	return 0;
}