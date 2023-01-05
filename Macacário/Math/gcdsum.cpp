#include <bitset>
#include <vector>
using namespace std;
#define MAXN 200009

typedef unsigned long long ll;
int phi[MAXN], sievesize;
ll f[MAXN];

void gcdSieve(int n) {
	sievesize = n+1;
	for(int i=0; i <= sievesize; i++) phi[i] = f[i] = 0;
	for(int i = 1; i <= sievesize; i++) {
		phi[i] += i;
		for(int j = i; j <= sievesize; j += i) {
			if (j > i) phi[j] -= phi[i];
			f[j] += j / i * phi[i];
		}
	}
}

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

ll F(ll N) {
	ll i = 0, p = primes[i];
	ll ans = 1;
	while (p * p <= N) {
		if (N % p == 0) {
			N /= p;
			ll prod = 1, e = 1;
			while (N % p == 0) {
				N /= p, e++;
				prod *= p;
			}
			ans *= prod * ((p-1)*e + p);
		}
		p = primes[++i];
	}
	ans *= 2*N-1;
	return ans;
}

/*
 * UVa 11424
 */

#include <cstdio>
ll sum[MAXN];
 
int main() {
	gcdSieve(MAXN-2);
	sieve(MAXN-2);
	sum[0] = 0;
	for(int i=1; i<MAXN; i++) sum[i] = F(i) + sum[i-1];
	ll N;
	while(scanf("%llu", &N), N) {
		printf("%llu\n", sum[N] - N*(N+1)/2);
	}
	return 0;
}