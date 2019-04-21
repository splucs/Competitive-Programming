#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define MAXN 100009
#define FOR(x,n) for(int x=0;x<n;x++)
#define FOR1(x,n) for(int x=1;x<=n;x++)
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;

int n;
vector<int> g[MAXN];
int dp1[MAXN], dp2[MAXN], dp3[MAXN];

int low2(vector<ii> &s, int v) {
	if (sz(s) < 2) return INF;
	int t1 = s[0].fi, t2 = s[1].fi;
	if (s[0].se == v) {
		if (sz(s) < 3) return INF;
		t1 = s[2].fi;
	}
	if (s[1].se == v) {
		if (sz(s) < 3) return INF;
		t2 = s[2].fi;
	}
	return t1 + t2;
}

int DP1(const int u);
int DP2(const int u);
int DP3(const int u);

int DP1(const int u) {
	int &ans = dp1[u];
	if (ans >= 0) return ans;
	ans = 0;
	for(int v : g[u]) {
		ans += DP2(v);
	}
	return ans;
}


int DP2(const int u) {
	int &ans = dp2[u];
	if (ans >= 0) return ans;
	vector<ii> low;
	int s2 = 0;
	for(int v : g[u]) {
		low.pb({DP2(v) - DP1(v), v});
		s2 += DP2(v);
	}
	sort(all(low));
	ans = DP1(u);
	for(int v : g[u]) {
		s2 -= DP2(v);
		ans = max(ans, DP3(v) + s2 - low2(low, v));
		s2 += DP2(v);
	}
	return ans;
}

int DP3(const int u) {
	int &ans = dp3[u];
	if (ans >= 0) return ans;
	if (sz(g[u]) < 2) return ans = DP1(u);
	vector<ii> low;
	int s2 = 0;
	for(int v : g[u]) {
		low.pb({DP2(v) - DP1(v), v});
		s2 += DP2(v);
	}
	sort(all(low));
	ans = DP2(u);
	ans = max(ans, 1 + s2 - low2(low, -1));
	return ans;
}

int main() {
	mset(dp1, -1);
	mset(dp2, -1);
	mset(dp3, -1);
	int n;
	scanf("%d", &n);
	for(int u = 2; u <= n; u++) {
		int p;
		scanf("%d", &p);
		g[p].pb(u);
	}
	printf("%d\n", DP1(1));
	/*FOR1(u, n) {
		printf("dp1[%d] = %d\n", u, dp1[u]);
	}
	FOR1(u, n) {
		printf("dp2[%d] = %d\n", u, dp2[u]);
	}
	FOR1(u, n) {
		printf("dp3[%d] = %d\n", u, dp3[u]);
	}*/
	return 0;
}
