#include <bits/stdc++.h>
using namespace std;
#define MAXN 1029
#define MAXM 1000009
#define INF 0x3f3f3f3f
#define MOD 1000000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mset(x, y) memset(&x, y, sizeof x)
#define sz(x) int(x.size())
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

int dp[MAXN], val[MAXN];
vector<int> avail[MAXN], g[MAXN];
bitset<MAXN> path[MAXN];

int cross[MAXN][MAXN], crossu[MAXN][MAXN];
int getcross(int u, int v) {
	bitset<MAXN> mid;
	for(int i : avail[u]) {
		mid |= path[i];
	}
	for(int j : avail[v]) {
		if (mid[j]) return 1;
	}
	return 0;
}

int getcrossu(int u, int v) {
	for(int j : avail[v]) {
		if (path[u][j]) return 1;
	}
	return 0;
}

int dfs(int u, int p) {
	dp[u] = 0;
	for(int &v : g[u]) {
		if (v == p) swap(v, g[u].back());
	}
	if (g[u].back() == p) g[u].pop_back();
	int ans = 0;
	for(int v : g[u]) ans += dfs(v, u);
	int m = g[u].size();
	FOR(i, m) FOR(j, i) {
		cross[g[u][i]][g[u][j]] = getcross(g[u][i], g[u][j]);
	}
	FOR(i, m) {
		crossu[u][g[u][i]] = getcrossu(u, g[u][i]);
	}
	FOR(mask, (1<<m)) {
		if (mask == 0) dp[mask] = 0;
		else {
			int lb = 0;
			while(!(mask & (1<<lb))) lb++;
			int lv = g[u][lb];
			dp[mask] = dp[mask^lb] + crossu[u][lv];
			for(int nb = lb+1; nb < m) {
				if (!(mask & (1<<nb))) continue;
				cur = 0;
				v = g[u][nb];
				for(int w : avail[v]) {
					if (path[])
				}
			}
		}
	}
	ans += dp[(1<<m)-1];
	return ans;
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int n, m;
		scanf("%d", &n);
		FOR1(u, n) g[u].clear();
		mset(path, 0);
		FOR(i, n-1) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].pb(v); g[v].pb(u);
		}
		FOR1(u, n) computeprv(u);
		scanf("%d", &m);
		mset(path, 0);
		FOR(i, m) {
			int u, v;
			scanf("%d %d", &u, &v);
			path[u][v] = 1;
			path[v][u] = 1;
		}
		FOR(i, MAXN) FOR(j, MAXN) {
			dp1[i][j] = -1;
			dp2[i][j][0] = dp2[i][j][1] = -1;
		}
		printf("%d\n", DP1(1, 0));
	}
	return 0;
}