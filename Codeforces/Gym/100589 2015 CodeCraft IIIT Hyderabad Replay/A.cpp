#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 100009
#define LOGN 17
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define fi first
#define se second
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;

map<int, int> sub[MAXN];
vector<ii> inter[MAXN];
bool squery[MAXN], lquery[MAXN];

void merge(int u, int v) {
	if (sub[u].size() < sub[v].size()) {
		sub[u].swap(sub[v]);
	}
	for(ii pp : sub[v]) {
		sub[u][pp.fi] += pp.se;
	}
	sub[v].clear();
}

vector<int> g[MAXN];
int n, m;

void dfs(int u, int p, int h) {
	for(int v : g[u]) {
		if (v == p) continue;
		dfs(v, u, h+1);
		merge(u, v);
	}
	if (lquery[h]) sub[u][h]++;
	if (squery[u]) inter[u] = vector<ii>(all(sub[u]));
}

int op[MAXN], l[MAXN], x[MAXN];
ll val[MAXN];

int main() {
	scanf("%d %d", &n, &m);
	FOR(j, n-1) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	mset(squery, false);
	mset(lquery, false);
	FOR(j, m) {
		scanf("%d", &op[j]);
		if (op[j] == 1) {
			scanf("%d %d", &l[j], &x[j]);
			lquery[l[j]] = true;
		}
		else {
			scanf("%d", &x[j]);
			squery[x[j]] = true;
		}
	}
	dfs(1, -1, 0);
	FOR(j, m) {
		if (op[j] == 1) {
			val[l[j]] += x[j];
		}
		else {
			ll ans = 0;
			for(ii pp : inter[x[j]]) {
				ans += pp.se*val[pp.fi];
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}