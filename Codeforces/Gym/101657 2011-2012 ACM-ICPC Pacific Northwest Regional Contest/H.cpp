#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define INF 1e+30

int main() {
	double a, b, c, d, m, t;
	while(scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &m, &t) != EOF) {
		double hi = INF;
		double lo = 0.0;
		while(fabs(hi-lo) > EPS) {
			double v = (hi+lo)/2.0;
			if (m*a*v*v*v + m*b*v*v + m*c*v + m*d > t) hi = v;
			else lo = v;
		}
		double v = (hi+lo)/2;
		printf("%.2f\n", v - 0.005);
	}
	return 0;
}