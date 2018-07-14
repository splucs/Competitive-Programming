#include <cstdio>
#include <algorithm>
using namespace std;

template <typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template<typename T>
T modMul(T a, T b, T m) {
	T x = 0, y = a % m;
	while (b > 0) {
		if (b % 2 == 1) x = (x + y) % m;
		y = (y * 2) % m;
		b /= 2;
	}
	return x % m;
}

/*
 * Pollard-Rho factorization
 * use only for n > 9*10^13
 */

template<typename T>
T pollard(T n) {
	int i = 0, k = 2, d;
	T x = 3, y = 3;
	while (true) {
		i++;
		x = (modMul(x, x, n) + n - 1) % n;
		d = gcd(abs(y - x), n);
		if (d != 1 && d != n) return d;
		if (i == k) y = x, k *= 2;
	}
}

/*
 *TEST MATRIX
 */
#include <cstdlib>

int main()
{
	long long n;
	while(scanf(" %I64d", &n)!=EOF) {
		long long r = pollard(n);
		printf("%I64d->%I64d\n", n, r);
		if (n%r != 0) {
			printf("Failed on test\n");
		}
	}
	return 0;
}