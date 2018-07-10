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
 * O(k*logn*logn*logn)
 */

typedef long long ll;

bool miller(ll n, ll a) {
	if (a >= n) return 1;
	ll s = 0, d = n-1;
	while (d%2 == 0 and d) d >>= 1, s++;
	ll x = modExp(a, d, n);
	if (x == 1 or x == n-1) return 1;
	for (int r = 0; r < s; r++, x = modMul(x,x,n)) {
		if (x == 1) return 0;
		if (x == n-1) return 1;
	}
	return 0;
}

bool isPrime(ll n) {
	int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
	for (int i = 0; i < 15; ++i)
		if (!miller(base[i], n)) return false;
	return true;
}

/*
 * TEST MATRIX
 */

#include <cstdio>
#include <cstdlib>

bool brutePrime(ll n) {
	if (n <= 1) return false;
	for(ll i = 2; i*i <= n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}

bool test(int ntest) {
	for(int t = 1; t <= ntest; t++) {
		ll n = rand();
		if (brutePrime(n) != isPrime(n)) {
			printf("failed on test %lld, prime = %d\n", n, brutePrime(n));
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(10000);
	return 0;
}
