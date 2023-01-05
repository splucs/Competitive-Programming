#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
typedef long long ll;
typedef pair<ll, ll> ii;

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	set<ll> row, col, mdiag, sdiag;
	FOR(i, k) {
		int t, x, y;
		scanf("%d %d %d", &t, &x, &y);
		if (t & 1) {
			row.insert(x);
			col.insert(y);
		}
		if (t & 2) {
			mdiag.insert(x+y);
			sdiag.insert(x-y);
		}
	}
	ll ans = n*1ll*m;
	ans -= row.size()*1ll*m;
	ans -= col.size()*1ll*n;
	ans += row.size()*1ll*col.size();
	for(ll s : mdiag) {
		set<ii> inter;
		for(ll x : row) {
			ll y = s-x;
			if (x >= 1 && x <= n && y >= 1 && y <= m) inter.insert({x, y});
		}
		for(ll y : col) {
			ll x = s-y;
			if (x >= 1 && x <= n && y >= 1 && y <= m) inter.insert({x, y});
		}
		ll cur = s-1;
		if (s-1 > n) cur -= s-1-n;
		if (s-1 > m) cur -= s-1-m;
		ans -= cur;
		ans += inter.size();
	}
	for(ll d : sdiag) {
		set<ii> inter;
		for(ll x : row) {
			ll y = x-d;
			if (x >= 1 && x <= n && y >= 1 && y <= m) inter.insert({x, y});
		}
		for(ll y : col) {
			ll x = d+y;
			if (x >= 1 && x <= n && y >= 1 && y <= m) inter.insert({x, y});
		}
		for(ll s : mdiag) {
			if ((d+s)%2 != 0) continue;
			ll x = (s+d)/2;
			ll y = (s-d)/2;
			if (x >= 1 && x <= n && y >= 1 && y <= m) inter.insert({x, y});
		}
		ll s = n+1-d;
		ll cur = s-1;
		if (s-1 > n) cur -= s-1-n;
		if (s-1 > m) cur -= s-1-m;
		ans -= cur;
		ans += inter.size();
	}
	printf("%lld\n", ans);
	return 0;
}