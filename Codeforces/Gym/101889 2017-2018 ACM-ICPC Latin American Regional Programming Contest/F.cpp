#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;

struct SegmentTree {
	vector<ll> a;
	int n;
	SegmentTree(int sz) {
		for(n = 1; n < sz; n <<= 1);
		a.assign(n<<1, 0);
	}
	void update(int i, ll x) {
		if (a[i+=n] > x) return;
		a[i] = x;
		for(i >>= 1; i; i>>=1)
			a[i] = max(a[i<<1], a[1+(i<<1)]);
	}
	ll query(int l, int r) {
		ll ans = 0;
		for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = max(ans, a[l++]);
			if (r & 1) ans = max(ans, a[--r]);
		}
		return ans;
	}
};

int n;
ll x[MAXN], y[MAXN], c[MAXN];
vector<int> byx[MAXN];
ll dp[MAXN];

int main() {
	scanf("%d", &n);
	map<ll, ll> reduce;
	map<ii, ll> values;
	FOR(i, n) {
		scanf("%lld %lld %lld", &x[i], &y[i], &c[i]);
		reduce[x[i]] = 0;
		reduce[y[i]] = 0;
	}
	int cnt = 0;
	for(auto &p : reduce) {
		p.se = cnt++;
	}
	FOR(i, n) {
		x[i] = reduce[x[i]];
		y[i] = reduce[y[i]];
		values[{x[i], y[i]}] += c[i];
	}
	n = 0;
	for(auto p : values) {
		x[n] = p.fi.fi;
		y[n] = p.fi.se;
		c[n] = p.se;
		n++;
	}
	FOR(i, n) byx[x[i]].pb(i);
	SegmentTree st(cnt);
	ll ans = 0;
	FOR(xt, cnt) {
		for(int i : byx[xt]) {
			dp[i] = c[i] + st.query(0, y[i]-1);
			ans = max(ans, dp[i]);
		}
		for(int i : byx[xt]) {
			st.update(y[i], dp[i]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}