#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

int main() {
	double r, d, x, y, h;
	int ans = 0, n;
	scanf("%lf %lf %d", &r, &d, &n);
	while(n--) {
		scanf("%lf %lf %lf", &x, &y, &h);
		if (hypot(x, y) - h + EPS >= r-d && hypot(x, y) + h <= r + EPS) ans++;
	}
	printf("%d\n", ans);
	return 0;
}