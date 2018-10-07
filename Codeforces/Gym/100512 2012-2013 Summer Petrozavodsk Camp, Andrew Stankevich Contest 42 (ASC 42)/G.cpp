#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

vi g[MAXN];
int d[MAXN], deg[MAXN], n, m;
bool vis[MAXN];

void dfs(int u) {
	if (vis[u]) return;
	vis[u] = true;
	for(int v : g[u]) {
		dfs(v);
		d[u] = min(d[u], d[v]);
	}
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("grand.in", "r", stdin);
	freopen("grand.out", "w", stdout);
	#endif
	while(scanf("%d", &n), n) {
		FOR1(u, n) {
			scanf("%d", &d[u]);
			g[u].clear();
			vis[u] = false;
			deg[u] = 0;
		}
		scanf("%d", &m);
		FOR(j, m) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			deg[v]++;
		}
		FOR1(u, n) dfs(u);
		set<ii> pq;
		int dis = 0;
		vi ans;
		FOR1(u, n) {
			if (deg[u] == 0) pq.insert({d[u], u});
		}
		int t = 1;
		while(!pq.empty()) {
			int u = pq.begin()->se;
			pq.erase(pq.begin());
			ans.pb(u);
			dis = max(dis, t-d[u]);
			t++;
			for(int v : g[u]) {
				deg[v]--;
				if (deg[v] == 0) pq.insert({d[v], v});
			}
		}
		printf("%d\n", dis);
		for(int u : ans) printf("%d ", u);
		printf("\n");
	}
	return 0;
}