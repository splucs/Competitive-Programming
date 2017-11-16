#include <bits/stdc++.h>
using namespace std;
#define MAXX 2000000

int main() {
	double n, p;
	while(scanf("%lf %lf", &n, &p) != EOF) {
		double dx = p/(n+1);
		double ans = dx;
		for(int x=2; x<MAXX; x++) {
			dx *= (n+x-p)/(n+x) * x/(x-1);
			if (dx > ans) ans = dx;
		}
		printf("%.11f\n", ans);
	}
	return 0;
}