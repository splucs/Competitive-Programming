#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

typedef unsigned long long ll;

bitset<MAXN> bs;
vector<ll> primes;
ll sievesize, eulerPhi[MAXN], sumDiv[MAXN];

void sieve(ll n) {
	sievesize = n + 1;
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 1; i <= sievesize; i++) eulerPhi[i] = i;
	for (ll i = 2; i <= sievesize; i++) {
		if (!bs[i]) continue;
		for (ll j = i; j <= (ll)sievesize; j += i) {
			if (i != j) bs[j] = 0;
			eulerPhi[j] -= eulerPhi[j] / i;
		}
		primes.push_back(i);
	}
	memset(&sumDiv, 0, sizeof sumDiv);
	for (ll i = 1; i <= sievesize; i++) {
		for(ll j = i; j <= sievesize; j += i) sumDiv[j] += i;
	}
}

ll EulerPhi(ll N) {
	if (N < MAXN) return eulerPhi[N];
	ll i = 0, p = primes[i], ans = N;
	while (p * p <= N) {
		if (N % p == 0) ans -= ans / p;
		while (N % p == 0) N /= p;
		p = primes[++i];
	}
	if (N != 1) ans -= ans / N;
	return ans;
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
	// special case if N is a prime
	if (N != 1) factors.push_back(ii(N, 1));
	return factors;
}

ll bt1(int i, ll fac, vector<ii> & pf) {
	if (i == -1) return fac;
	ll ans = 0, prod = 1;
	for(int j=0; j<=pf[i].second; j++) {
		ans += bt1(i-1, fac*prod, pf);
		prod *= pf[i].first;
	}
	return ans;
}

ll SumDiv(ll N) {
	if (N < MAXN) return sumDiv[N];
	vector<ii> pf = primeFactors(N);
	return bt1(pf.size()-1, 1, pf);
}

ll ans, N;
void bt2(int i, ll fac, vector<ii> & pf) {
	if (i == -1) {
		ans += fac*fac;
		ans -= SumDiv(N/fac)*EulerPhi(fac);
		return ;
	}
	ll prod = 1;
	for(int j=0; j<=pf[i].second; j++) {
		bt2(i-1, fac*prod, pf);
		prod *= pf[i].first;
	}
}

int main() {
	int T;
	sieve(MAXN-2);
	scanf("%d", &T);
	while(T-->0) {
		scanf("%llu", &N);
		ans = 0;
		vector<ii> pf = primeFactors(N);
		bt2(pf.size()-1, 1, pf);
		printf("%llu\n", ans);
	}
	return 0;
}