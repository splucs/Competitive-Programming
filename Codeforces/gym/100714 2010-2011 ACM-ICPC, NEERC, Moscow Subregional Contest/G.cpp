#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009

typedef pair<double, double> dd;
dd c[MAXN];
double r[MAXN], x[MAXN];
int N;

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N; i++) {
		scanf("%lf %lf", &c[i].first, &c[i].second);
	}
	sort(c+1, c+1+N);
	for(int i=1; i<=N; i++) {
		x[i] = c[i].first;
		r[i] = c[i].second*14.0;
	}
	double ans = 0.0;
	for(int i=1; i<=N; i++){
		double phi1 = 1.0, phi2 = -1.0;
		if (r[i] > x[i]) phi1 = x[i]/r[i];
		for(int j=1; j<i; j++) {
			double dx = x[i]-x[j];
			if (r[i] + r[j] < abs(dx)) continue;
			else if (r[j] > abs(dx) + r[i]) phi1 = -1.0;
			else {
				phi1 = min(phi1, (dx*dx + r[i]*r[i] - r[j]*r[j])/(2*dx*r[i]));
			}
		}
		for(int j=i+1; j<=N; j++) {
			double dx = x[i]-x[j];
			if (r[i] + r[j] < abs(dx)) continue;
			else if (r[j] > abs(dx) + r[i]) phi2 = 1.0;
			else {
				phi2 = max(phi2, (dx*dx + r[i]*r[i] - r[j]*r[j])/(2*dx*r[i]));
			}
		}
		if (phi1 > phi2){
			ans += 2*M_PI*r[i]*r[i]*(phi1 - phi2);
		}
	}
	printf("%.6f\n", ans);
	return 0;
}