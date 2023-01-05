#include <bits/stdc++.h>
using namespace std;
#define MAXN 159
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI (acos(-1.0))
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) ((int)x.size())
typedef long long ll;
typedef pair<int, int> ii;

int n, r[MAXN], s[MAXN], sum[MAXN];
map<ll, int> dp[MAXN];

int getdp(int i, ll b) {
	assert(!dp[i].empty());
	auto it = dp[i].lower_bound(b);
	if (it == dp[i].end()) it--;
	return it->se;
}

int computedp(int i, ll b) {
	if (i == n) return dp[i][b] = 0;
	int v1 = (sum[i+1]-getdp(i+1, -b-r[i])) + s[i];
	if (b <= 0) return dp[i][b] = v1;
	int v2 = (sum[i]-getdp(i, -b+1));
	return dp[i][b] = max(v1, v2);
}

void compute(int i, ll l, ll r) {
	if (computedp(i, l) == computedp(i, r)) return;
	ll m = (l + r) / 2;
	if (r <= 0 && (r-l)%2 != 0) m--;
	compute(i, l, m);
	compute(i, m+1, r);
}

int main() {
	int a, b;
	scanf("%d %d %d", &n, &a, &b);
	FOR(i, n) scanf("%d %d", &r[i], &s[i]);
	int acum = 0;
	REP(i, n+1) {
		if (i < n) acum += s[i];
		sum[i] = acum;
		compute(i, -INFLL, 0);
		compute(i, 1, INFLL);
	}
	int ans1 = getdp(0, a-b);
	int ans2 = sum[0] - ans1;
	printf("%d %d\n", ans1, ans2);
	return 0;
}