#include <bits/stdc++.h>
using namespace std;
#define INF 1e+18
#define EPS 1e-9

double x, y, c;

bool reduce(double d) {
	double z = c/sqrt(y*y-d*d) + c/sqrt(x*x-d*d);
	return z > 1.0;
}

int main() {
	while(scanf("%lf %lf %lf", &x, &y, &c) != EOF) {
		double lo = 0;
		double hi = x > y ? y : x;
		while(fabs(hi - lo) > EPS) {
			double m = (hi + lo)/2.0;
			if (reduce(m)) hi = m;
			else lo = m;
		}
		printf("%.3f\n", hi);
	}
	return 0;
}