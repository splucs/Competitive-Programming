#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000

typedef long long ll;
ll sievesize;
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

ll EulerPhi(ll N) {
	ll i = 0, p = primes[i], ans = N;
	while (p * p <= N) {
		if (N % p == 0) ans -= ans / p;
		while (N % p == 0) N /= p;
		p = primes[++i];
	}
	if (N != 1) ans -= ans / N;
	return ans;
}

ll modExp(ll a, ll b, ll m) {
	if (b == 0) return 1%m;
	ll c = modExp(a, b/2, m);
	c = (c*c)%m;
	if (b % 2 != 0) c = (a*c)%m;
	return c;
}

ll exponial(ll n, ll m) {
	if (m == 1LL) return 0;
	if (n == 1LL) return 1;
	if(n <= 5LL) return modExp(n, exponial(n-1, m), m);
	ll phi = EulerPhi(m);
	ll z = exponial(n-1, phi);
	return modExp(n, phi+z, m);
}

int main() {
	ll n, m;
	sieve(MAXN-2);
	while(scanf("%I64d %I64d", &n, &m) != EOF) {
		printf("%I64d\n", exponial(n, m));
	}
	return 0;
}