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

template<typename T>
T modExp(T a, T b, T m) {
	if (b == 0) return (T)1;
	T c = modExp(a, b / 2, m);
	c = (c * c) % m;
	if (b % 2 != 0) c = (c*a) % m;
	return c;
}

/*
 * Miller-Rabin primality test
 * O(k*log^2n), k = 9
 * probabilistic, but proven correct for n < 2^64
 */

bool miller(long long n) {
	const int pn = 9;
	const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for (int i = 0; i < pn; i++)
		if (n % p[i] == 0) return n == p[i];
	if (n < p[pn - 1]) return false;
	long long s = 0, t = n - 1;
	while (~t & 1) t >>= 1, ++s;
	for (int i = 0; i < pn; ++i) {
		long long pt = modExp((long long)p[i], t, n);
		if (pt == 1) continue;
		bool ok = false;
		for (int j = 0; j < s && !ok; j++) {
			if (pt == n - 1) ok = true;
			pt = modMul(pt, pt, n);
		}
		if (!ok) return false;
	}
	return true;
}

/*
 * TEST MATRIX
 */

#include <cstdio>
#include <cstdlib>

bool brutePrime(long long n) {
	if (n <= 1) return false;
	for(long long i = 2; i*i <= n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}

bool test(int ntest) {
	for(int t = 1; t <= ntest; t++) {
		long long n = rand();
		if (brutePrime(n) != miller(n)) {
			printf("failed on test %lld, prime = %d\n", n, brutePrime(n));
			return false;
		}
		n = t;
		if (brutePrime(n) != miller(n)) {
			printf("failed on test %lld, prime = %d\n", n, brutePrime(n));
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(10000000);
	long long n;
	while(scanf("%lld", &n) != EOF) {
		printf("%lld is %sprime\n", n, miller(n) ? "" : "not ");
	}
	return 0;
}
