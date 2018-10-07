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
int n, m;
int q[MAXN], st, en;
bool vis[MAXN];
int per[MAXN], vised;

int bfs(int s) {
	st = en = 0;
	q[en++] = s;
	int ans = 1;
	vis[s] = true;
	while(en > st) {
		int u = q[st++];
		for(int v : g[u]) {
			vised++;
			if (vis[v]) continue;
			vis[v] = true;
			ans++;
			q[en++] = v;
		}
	}
	FOR(i, en) vis[q[i]] = false;
	return ans;
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("journey.in", "r", stdin);
	freopen("journey.out", "w", stdout);
	#endif

	srand(time(NULL));
	while(scanf("%d", &n), n) {
		scanf("%d", &m);
		FOR1(u, n) {
			g[u].clear();
			per[u] = u;
		}
		random_shuffle(per+1, per+1+n);
		FOR(j, m) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].pb(v);
		}
		vised = 0;
		ii ans = {-1, -1};
		FOR1(i, n) {
			if (vised > 500*n) break;
			int u = per[i];
			int k = bfs(u);
			ans = max(ans, {k, u});
		}
		printf("%d %d\n", ans.se, ans.fi);
	}
	return 0;
}