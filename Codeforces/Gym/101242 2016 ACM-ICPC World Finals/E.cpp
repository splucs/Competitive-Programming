#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define sz(x) int(x.size())
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
typedef long long ll;

ll modMul(ll a, ll b, ll m) {
	ll x = 0, y = a%m;
	while(b > 0) {
		if (b&1) x = (x+y)%m;
		y = (y*2)%m;
		b >>= 1;
	}
	return x%m;
}

ll pollard(ll n) {
	int k = 2;
	ll x = 3, y = 3;
	FOR1(i, 10000) {
		x = (modMul(x, x, n) + n - 1) % n;
		int d = __gcd(abs(y - x), n);
		if (d != 1 && d != n) return d;
		if (i == k) y = x, k <<= 1;
	}
	return 1;
}

void factorize(ll n, map<ll, int> &ans) {
	if (n > 90000000000000) {
		ll fac = pollard(n);
		if (fac == 1) {
			ans[n]++;
		}
		else {
			factorize(fac, ans);
			factorize(n/fac, ans);
		}
	}
	else {
		for(ll i = 2; i*i <= n; i++) {
			while(n % i == 0) {
				ans[i]++;
				n /= i;
			}
		}
		if (n > 1) ans[n]++;
	}
}

ll ans = 10, y, l;
ll low[30], cur[30];

void decompose(ll n, ll b, ll arr[]) {
	FOR(i, 30) {
		arr[i] = n%b;
		n /= b;
	}
}

bool check(ll b) {
	decompose(y, b, cur);
	FOR(i, 30) if (cur[i] > 9) return false;
	REP(i, 30) {
		if (cur[i] > low[i]) return true;
		if (cur[i] < low[i]) return false;
	}
	return true;
}

void iterate(int i, ll b, vector< pair<ll,int> > &fac) {
	if (i == sz(fac)) {
		if (check(b)) ans = max(ans, b);
		return;
	}
	FOR(j, fac[i].se+1) {
		iterate(i+1, b, fac);
		b *= fac[i].fi;
	}
}

void iterate(ll n) {
	map<ll, int> map_factors;
	factorize(n, map_factors);
	vector< pair<ll,int> > fac(all(map_factors));
	/*printf("factors: ");
	for(auto pp : fac) {
		printf(" %lld^%d", pp.fi, pp.se);
	}
	printf("\n");*/
	iterate(0, 1, fac);
}

int main() {
	scanf("%lld %lld", &y, &l);
	decompose(l, 10, low);
	FOR(i, 10) iterate(y-i);
	printf("%lld\n", ans);
	return 0;
}