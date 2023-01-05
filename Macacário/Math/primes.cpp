#include <bitset>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define MAXN 10000009

typedef long long int ll;
ll sievesize, numDiffp[MAXN];
bitset<MAXN> bs;
vector<ll> primes;

void sieve(ll n) {
	sievesize = n + 1;
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= sievesize; i++) {
		if (bs[i]) {
			for (ll j = i * i; j <= (ll)sievesize; j += i) bs[j] = 0;
			primes.push_back(i);
		}
	}
}

//O(sqrt(n)/logn), works if factors are less than the biggest prime in primes
bool isPrimeSieve(ll N) {
	if (N <= (ll)sievesize) return bs[N];
	for (int i = 0; i < (int)primes.size() && primes[i]*primes[i] <= N; i++)
		if (N % primes[i] == 0) return false;
	return true;
}

//O(sqrt(n))
bool isPrime(ll N) {
    if (N < 0) return isPrime(-N);
	for(ll i=2; i*i <= N; i++) {
		if (N % i == 0) return false;
	}
	return true;
}

//O(sqrt(n))
bool isPrimeFast(ll n) {
    if (n < 0) n = -n;
    if (n < 5 || n % 2 == 0 || n % 3 == 0)
        return (n == 2 || n == 3);
    ll maxP = sqrt(n) + 2;
    for (ll p = 5; p < maxP; p += 6) {
        if (p < n && n % p == 0) return false;
        if (p+2 < n && n % (p+2) == 0) return false;
	}
    return true;
}

typedef pair<ll, int> ii;
vector<ii> primeFactors(ll N) {
	vector<ii> factors;
	ll i = 0, p = primes[i];
	while (p * p <= N) {
		if (N % p == 0) {
			int cnt = 0;
			while (N % p == 0) N /= p, cnt++;
			factors.push_back(ii(p, cnt));
		}
		p = primes[++i];
	}
	if (N != 1) factors.push_back(ii(N, 1));
	return factors;
}

ll numDiv(ll N) {
	ll i = 0, p = primes[i], ans = 1;
	while (p * p <= N) {
		ll pw = 0;
		while (N % p == 0) { N /= p; pw++; }
		ans *= (pw + 1);
		p = primes[++i];
	}
	if (N != 1) ans *= 2;
	return ans;
}

ll eulerPhi(ll N) {
	ll i = 0, p = primes[i], ans = N;
	while (p * p <= N) {
		if (N % p == 0) ans -= ans / p;
		while (N % p == 0) N /= p;
		p = primes[++i];
	}
	if (N != 1) ans -= ans / N;
	return ans;
}

void numDiffp() {
	memset(numDiffp, 0, sizeof numDiffp);
	for (int i = 2; i < MAXN; i++)
		if (numDiffp[i] == 0)
			for (int j = i; j < MAXN; j += i)
				numDiffp[j]++;
}

int main() {
	sieve(MAXN); // can go up to 10^7 (need few seconds)
	printf("%d\n", isPrime(2147483647)); // 10-digits prime
	printf("%d\n", isPrime(136117223861LL)); // not a prime, 104729*1299709
	return 0;
}