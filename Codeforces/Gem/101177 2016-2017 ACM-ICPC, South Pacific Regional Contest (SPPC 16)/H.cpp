#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1LL<<60)

template <typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template<typename T>
T modExp(T a, T b, T m) {
    if (b == 0) return (T)1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c = (c*a) % m;
    return c;
}

typedef long long int ll;
typedef pair<ll, ll> ii;
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

vector<ii> primeFactors(ll N) {
	vector<ii> factors;
	ll i = 0, p = primes[i];
	while (p * p <= N) {
		int cnt = 0;
		while (N % p == 0) {
			N /= p;
			cnt++;
		}
		if (cnt > 0) factors.push_back(ii(p, cnt));
		p = primes[++i];
	}
	// special case if N is a prime
	if (N != 1) factors.push_back(ii(N, 1));
	return factors;
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

ll K;
ll qk(ll p, ll a) {
	if (a == 0) return 0;
	//if (a == 1) return p;
	if (p == 2) {
		if (a % 2 == 0) return modExp(2LL, a-2, INF)/gcd(modExp(2LL, a-2, INF), K);
		else {
			if (a == 1) return 1;
			return modExp(2LL, a-2, INF)/gcd(modExp(2LL, a-2, INF), K);
		}
	}
	else {
		ll phi = EulerPhi(modExp(p, a, INF));
		//printf("phi = %I64d\n", phi);
		return phi/gcd(phi, K);
	}
}

ll sk(ll p, ll a) {
	if (a >= K) return qk(p, a) + sk(p, a-K);
	else return qk(p, a) + 1;
}

ll solve(ll N) {
	ll ans = 1;
	vector<ii> fac = primeFactors(N);
	for(int i=0; i<(int)fac.size(); i++) {
		ll p = fac[i].first;
		ll a = fac[i].second;
		ans *= sk(p, a);
		//printf("qk(%I64d,%I64d) = %I64d\n", p, a, qk(p, a));
		//printf("sk(%I64d,%I64d) = %I64d\n", p, a, sk(p, a));
	}
	return ans;
}

int main() {
	ll N, Q;
	sieve(MAXN);
	while(scanf("%I64d %I64d %I64d", &K, &Q, &N) != EOF) {
		printf("%I64d\n", solve(N));
	}
	return 0;
}