#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-10
#define INF 1e+90

double csh(double x) {
	return (exp(x)+exp(-x))/2.0;
}

double snh(double x) {
	return (exp(x)-exp(-x))/2.0;
}

int main() {
	double s, d, a;
	scanf("%lf %lf", &d, &s);
	double hi = INF;
	double lo = 0;
	while(fabs(hi-lo) > EPS) {
		a = (hi+lo)/2;
		if (a*csh(d/(2*a)) - a < s) hi = a;
		else lo = a;
	}
	printf("%.9f\n", 2*a*snh(d/(2*a)));
	return 0;
}