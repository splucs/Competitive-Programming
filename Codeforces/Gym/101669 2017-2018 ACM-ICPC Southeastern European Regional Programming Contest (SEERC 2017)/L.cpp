#include <bits/stdc++.h>
#define MAXN 200009
#define MAXLOGN 20
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int n;
vector<int> g[2][MAXN];
set<int> sub[MAXN];
multiset<int> reach[MAXN];

void merge(int u, int v) {
	if (sz(sub[u]) < sz(sub[v])) {
		swap(sub[u], sub[v]);
		swap(reach[u], reach[v]);
	}

	for(int w : sub[v]) {
		reach[u].erase(w);
		sub[u].insert(w);
	}
	sub[v].clear();
	for(int w : reach[v]) {
		if (!sub[u].count(w)) reach[u].insert(w);
	}
	reach[v].clear();
}

void dfs(int u, int p, int k, int &minans, int &cntans) {
	sub[u].clear();
	sub[u].insert(u);
	reach[u] = multiset<int>(all(g[k^1][u]));

	for(int v : g[k][u]) {
		if (v == p) continue;
		dfs(v, u, k, minans, cntans);
		merge(u, v);
	}

	if (p == -1) return;
	int outedges = 1 + sz(reach[u]);
	
	/*printf("k=%d, edge %d-%d, outedges: %d\n", k, u, p, outedges);
	printf("sub:");
	for(int w : sub[u]) printf(" %d", w);
	printf("\n");
	printf("reach:");
	for(int w : reach[u]) printf(" %d", w);
	printf("\n\n");*/

	if (outedges > minans) return;
	if (outedges < minans) {
		minans = outedges;
		cntans = 0;
	}
	cntans++;
}

int main() {
	scanf("%d", &n);
	FOR(k, 2) FOR(i, n-1) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[k][u].pb(v);
		g[k][v].pb(u);
	}

	int minans = INF, cntans = 0;
	dfs(1, -1, 0, minans, cntans);
	dfs(1, -1, 1, minans, cntans);

	if (minans == 2) {
		assert(cntans % 2 == 0);
		cntans /= 2;
	}
	printf("%d %d\n", minans, cntans);

	return 0;
}