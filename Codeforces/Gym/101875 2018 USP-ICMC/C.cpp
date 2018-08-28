#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define MAXN 1000009
#define MOD 1000000007
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef long long ll;
typedef pair<ll, ll> ii;

map<ll, int> divi;
vector<int> fac;
vector<int> expn;

int pd[1003][30003];

vector<ll> primes;
ll ssz;
bitset<MAXN> bs;

void sieve(ll n) {
	ssz = n+1;
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= ssz; i++) {
		if (bs[i]) {
			for (ll j = i*i; j <= (ll) ssz; j += i) bs[j] = 0;
			primes.pb(i);
		}
	}
}

int calc(int rem, int st) {
	if (st == expn.size()) return (rem == 1) ? 1 : 0;

	if (pd[rem][st] != -1) return pd[rem][st];
	
	int& ans = pd[rem][st];
	ans = 0;
	FOR(k, fac.size()) {
		if (fac[k] > expn[st] || fac[k] > rem) break;
		if (rem%fac[k] != 0) continue;

		ans += calc(rem/fac[k], st+1);
		if (ans >= MOD) ans -= MOD;
	}
	return ans;
}

int main() {
	int b, n;
	ll v;

	scanf("%d %d", &b, &n);
	sieve(1000000);

	FOR(i, n) {
		scanf("%lld", &v);
		// fatora v e pra cada diviisor faz divi[k] += fac
		for (int k = 0; k < primes.size() && primes[k]*primes[k] <= v; k++) {
			if (v%primes[k] == 0) {
				int cnt = 0;
				while (v%primes[k] == 0) {
					cnt++;
					v /= primes[k];
				}
				divi[primes[k]] += cnt;
			}
		}

		if (v != 1) divi[v]++;
	}

	for (auto& pa : divi) {
	//	printf("%lld %d\n", pa.first, pa.second);
		expn.pb(pa.second + 1);
	}

	for (int i = 1; i*i <= b; i++) {
		if (b%i == 0) {
			fac.pb(i);
			if (i != b/i) fac.pb(b/i);
		}
	}

	sort(all(fac));
	memset(pd, -1, sizeof(pd));
	printf("%d\n", calc(b, 0));
}