#include <cmath>

/*
 * Simpson Rule for integration
 */

double f(double x) { return cos(x); }

double simpson(double a, double b, int n = 1e6) {
	double h = (b - a) / n, s = f(a) + f(b);
	for (int i = 1; i < n; i += 2) s += 4*f(a+h*i);
	for (int i = 2; i < n; i += 2) s += 2*f(a+h*i);
	return s*h/3;
}

/*
 * TEST MATRIX
 */

#include <cstdio>
#include <cmath>

bool test(int n) {
	for(int i = 0; i < n; i++) {
		double area = simpson(0, i);
		double exact = sin(i*1.0);
		if (fabs(area - exact) > 1e+18) {
			printf("error at %d = %.20f\n", i, fabs(area - exact));
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(100);
	return 0;
}