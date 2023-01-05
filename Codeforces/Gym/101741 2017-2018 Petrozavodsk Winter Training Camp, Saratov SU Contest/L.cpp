#include <bits/stdc++.h>
#define FOR(x, n) for(int x=0; x<n; x++)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
#define pb push_back
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define MAXN 500009
#define MAXLOGN 18
#define MOD 1000000007
using namespace std;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;

vector<ii> adj[MAXN];
vector<int> g[MAXN], revg[MAXN];
int n, m;

ll dist[MAXN];
void dijkstra(int s) {
	FOR1(u, n) {
		dist[u] = INFLL;
		revg[u].clear();
		g[u].clear();
	}
	set<pair<ll, int> > pq;
	dist[s] = 0;
	pq.insert({dist[s], s});
	while(!pq.empty()) {
		int u = pq.begin()->se;
		pq.erase(pq.begin());
		for(ii pp : adj[u]) {
			int v = pp.se;
			ll w = pp.fi;
			if (dist[v] > dist[u] + w) {
				revg[v].clear();
				pq.erase({dist[v], v});
				dist[v] = dist[u] + w;
				pq.insert({dist[v], v});
			}
			if (dist[v] == dist[u] + w) {
				revg[v].pb(u);
			}
		}
	}
}

bool isnode[MAXN];

void transformGraph() {
	int cnt = n;
	mset(isnode, false);
	FOR1(u, n) {
		isnode[u] = true;
		for(int &v : revg[u]) {
			int tmp = v;
			v = ++cnt;
			revg[v].clear(); g[v].clear();
			revg[v].pb(tmp);
			g[tmp].pb(v);
			g[v].pb(u);
			//printf("%d->%d becomes %d->%d->%d\n", tmp, u, tmp, v, u);
		}
	}
	n = cnt;
}

vi dtree[MAXN];
int sdom[MAXN], dom[MAXN], idom[MAXN];
int dsu[MAXN], best[MAXN];
int par[MAXN], num[MAXN], rev[MAXN], cnt;

int find(int x) {
	if (x == dsu[x]) return x;
	int y = find(dsu[x]);
	if (sdom[best[x]] > sdom[best[dsu[x]]]) best[x] = best[dsu[x]];
	return dsu[x] = y;
}

void dfs(int u) {
	num[u] = cnt;
	rev[cnt++] = u;
	for (int v : g[u]) {
		if (num[v] >= 0) continue;
		dfs(v);
		par[num[v]] = num[u];
	}
}

void dominator() {
	FOR1(u, n) {
		num[u] = -1;
		dtree[u].clear();
		dsu[u] = best[u] = sdom[u] = u;
	}
	cnt = 0;
	dfs(1);
	for(int j = cnt-1, u; u = rev[j], j > 0; j--) {
		for(int v : revg[u]) {
			int y = num[v];
			if (y == -1) continue;
			find(y);
			if (sdom[best[y]] < sdom[j]) sdom[j] = sdom[best[y]];
		}
		dtree[sdom[j]].pb(j);
		int x = dsu[j] = par[j];
		for(int z : dtree[x]) {
			find(z);
			if (sdom[best[z]] < x) dom[z] = best[z];
			else dom[z] = x;
		}
		dtree[x].clear();
	}
	idom[1] = -1;
	for(int i = 1; i < cnt; i++) {
		if (sdom[i] != dom[i]) dom[i] = dom[dom[i]];
		idom[rev[i]] = rev[dom[i]];
		dtree[rev[dom[i]]].pb(rev[i]);
	}
}

int ans[MAXN];
int solve(int u) {
	ans[u] = isnode[u];
	for(int v : dtree[u]) {
		//printf("dtree %d->%d\n", u, v);
		ans[u] += solve(v);
	}
	return ans[u];
}

int ansorder[MAXN];

int main() {
	scanf("%d %d", &n, &m);
	map<ii, int> uv;
	FOR(j, m) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		adj[u].pb({w, v});
		adj[v].pb({w, u});
		uv[{u, v}] = j;
		uv[{v, u}] = j;
	}
	dijkstra(1);
	transformGraph();
	dominator();
	solve(1);
	FOR1(u, n) {
		if (!isnode[u]) continue;
		for(int v : g[u]) {
			assert(!isnode[v]);
			for(int w : g[v]) {
				ansorder[uv[{u, w}]] = ans[v];
			}
		}
	}
	FOR(j, m) {
		printf("%d\n", ansorder[j]);
	}
	return 0;
}