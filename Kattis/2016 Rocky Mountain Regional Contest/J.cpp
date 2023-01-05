#include <bits/stdc++.h>
using namespace std;
#define MAXN 19
#define INF 1e+9
#define EPS 1e-9

double t[MAXN], T, a[MAXN], b[MAXN], c[MAXN];
int N;

double check(double slope) {
	double ans = 0.0;
	for(int i=0; i<N; i++) {
		t[i] = (slope-b[i])/(2*a[i]);
		if (t[i] < 0.0) t[i] = 0.0;
		ans += t[i];
	}
	return ans;
}

double bs() {
	double hi = INF;
	double lo = 0.0;
	while(hi - lo > EPS) {
		double mid = (hi+lo)/2.0;
		if (check(mid) > T) lo = mid;
		else hi = mid;
	}
	double ans = 0.0;
	for(int i=0; i<N; i++) {
		//printf("t[%d] = %.10f\n", i, t[i]);
		ans += a[i]*t[i]*t[i] + b[i]*t[i] + c[i];
	}
	return ans/N;
}

int main() {
	scanf("%d %lf", &N, &T);
	for(int i=0; i<N; i++) {
		scanf("%lf %lf %lf", &a[i], &b[i], &c[i]);
	}
	printf("%.10f\n", bs());
	return 0;
}