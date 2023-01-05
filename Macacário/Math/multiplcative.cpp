#include <vector>
#include <bitset>
using namespace std;

/*
 * Linear sieve of Eratosthenes and computing multiplative functions
 */

vector<int> primes;
bool isprime[MAXN];
int f[MAXN], cnt[MAXN];

int F(int p, int k) {
	int q = 1;
	for(int i = 1; i < k; i++) q *= p;
	return q*(p-1);
}

void sieve(int n) {
	std::fill (is_composite, is_composite + n, false);
	for (int i = 2; i <= n; ++i) {
		if (isprime[i]) {
			primes.push_back(i);
			f[i] = F(i, 1); cnt[i] = 1;
		}
		for (int j = 0; j < primes.size(); ++j) {
			isprime[i * primes[j]] = false;
			if (i % primes[j] == 0) {
				f[i * primes[j]] = f[i] / cnt[i] * (cnt[i] + 1);
				cnt[i * primes[j]] = cnt[i] + 1;
				break;
			} else {
				f[i * primes[j]] = f[i] * f[primes[j]];
				cnt[i * primes[j]] = 1;
			}
		}
	}
}