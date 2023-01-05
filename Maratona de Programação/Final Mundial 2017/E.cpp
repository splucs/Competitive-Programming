#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 1e+15
#define EPS 1e-9

double d[MAXN], s[MAXN], t;

int main() {
	int n;
	scanf("%d %lf", &n, &t);
	double lo = -INF, hi = INF, c, cur;
	for(int i=1; i<=n; i++) {
		scanf("%lf %lf", &d[i], &s[i]);
		hi = min(hi, s[i]);
	}
	while(hi-lo > EPS) {
		c = (lo+hi)/2;
		cur = 0;
		for(int i=1; i<=n; i++) {
			cur += d[i]/(s[i] - c);
		}
		if (cur > t) hi = c;
		else lo = c;
	}
	printf("%.9f\n", -c);
	return 0;
}