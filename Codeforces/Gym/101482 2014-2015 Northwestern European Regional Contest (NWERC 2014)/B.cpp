#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

double vw, vb, distg[MAXN], distd[MAXN];
double xmax, xmin, ymax, ymin;
double xg, yg, xd, yd, x[MAXN], y[MAXN];
int N;

int main() {
	scanf("%lf %lf", &vw, &vb);
	scanf("%lf %lf %lf %lf", &xmin, &ymin, &xmax, &ymax);
	scanf("%lf %lf %lf %lf", &xg, &yg, &xd, &yd);
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%lf %lf", &x[i], &y[i]);
		distd[i] = hypot(x[i]-xd, y[i]-yd) / vw;
		distg[i] = hypot(x[i]-xg, y[i]-yg) / vw;
	}
	double ans = hypot(xd-xg, yd-yg) / vw;
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			ans = min(ans, hypot(x[i]-x[j], y[i]-y[j]) / vb + distd[i] + distg[j]);
		}
	}
	printf("%.9f\n", ans);
	return 0;
}