#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define INF 1e33
#define EPS 1e-9
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define sz(x) ((int)x.size())
typedef long long ll;

double p[MAXN], op[MAXN], h[MAXN];

int main() {
	double x, g = 1;
	int n, b;
	scanf("%lf %d %d", &x, &n, &b);
	FOR(i, n) scanf("%lf %lf", &op[i], &h[i]);
	double ans = INF;
	FOR1(j, b+1) {
		double dx = x/j;
		double vx = sqrt(dx*g/2);
		bool ok = true;
		FOR(i, n) p[i] = op[i];
		FOR(jt, j) {
			FOR(i, n) {
				if (fabs(p[i]) < EPS || fabs(p[i]-dx) < EPS) {
					ok = false; break;
				}
				if (p[i] > dx || p[i] < 0) continue;
				vx = min(vx, sqrt(g*p[i]*(dx-p[i])/(2*h[i])));
			}
			FOR(i, n) p[i] -= dx;
		}
		if (!ok) continue;
		double vy = dx*g/(2*vx);
		double v = hypot(vx, vy);
		ans = min(v, ans);

	}
	printf("%.20f\n", ans);
	return 0;
}