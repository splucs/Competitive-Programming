#include <cstdio>
#include <bitset>
#include <vector>
using namespace std;
#define MAXN 1000009

typedef long long int ll;
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

ll extGcd(ll a, ll b, ll & x, ll & y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    else {
        ll g = extGcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}

ll modInv(ll a, ll m) {
    ll x, y;
    extGcd(a, m, x, y);
    return (x % m + m) % m;
}

ll EulerPhi(ll N) {
	ll PF_idx = 0, PF = primes[PF_idx], ans = N;
	while (PF * PF <= N) {
		if (N % PF == 0) ans -= ans / PF;
		while (N % PF == 0) N /= PF;
		PF = primes[++PF_idx];
	}
	if (N != 1) ans -= ans / N;
	return ans;
}

ll exp(ll b, ll e, ll m){
	if (e == 0) return 1;
	ll a = exp(b, e/2, m);
	a = (a*a) % m;
	if (e%2 != 0) a = (a*b) % m;
	return a;
}

int main()
{
	ll N, E, C;
	sieve(MAXN - 2);
	while(scanf("%lld %lld %lld", &N, &E, &C)!=EOF){
		ll phiN = EulerPhi(N);
		ll D = modInv(E, phiN);
		ll M = exp(C, D, N);
		printf("%lld\n", M);
	}
	return 0;
}