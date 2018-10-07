#include <vector>
#include <bitset>
using namespace std;
#define MAXN 1000009
#include <cstdio>

/*
 * Linear sieve of Eratosthenes and computing multiplative functions
 */

vector<int> primes;
bitset<MAXN> bs;
int f[MAXN], pw[MAXN];

int g(int p, int k) {
	if (p == 1) return 1;
	return (k==0) - (k==1);
	//int q = 1;
	//for(int i = 1; i < k; i++) q *= p;
	//return q*(p-1);
}

void sieve(int n) {
	bs.set(); bs[0] = bs[1] = 0;
	primes.clear(); f[1] = g(1, 1);
	for (int i = 2; i <= n; i++) {
		if (bs[i]) {
			primes.push_back(i);
			f[i] = g(i, 1); pw[i] = 1;
		}
		for (int j = 0; j < primes.size() && i*1ll*primes[j] <= n; j++) {
			bs[i * primes[j]] = 0;
			if (i % primes[j] == 0) {
				int pwr = 1;
				for(int k = 0; k < pw[i]; k++) pwr *= primes[j];
				f[i * primes[j]] = f[i / pwr] * g(primes[j], pw[i]+1);
				pw[i * primes[j]] = pw[i] + 1;
				break;
			} else {
				f[i * primes[j]] = f[i] * f[primes[j]];
				pw[i * primes[j]] = 1;
			}
		}
	}
}

/*
 * TEST MATRIX
 */
#include <cstdio>

void test(int n) {
	sieve(n);
	for(int i = 1; i <= n; i++) {
		printf("f[%3d] = %2d, %d is %sprime, \n", i, f[i], i, bs[i] ? "" : "not ");
	}
}

int main() {
	test(100);
}