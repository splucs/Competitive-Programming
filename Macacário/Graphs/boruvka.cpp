#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 200009
typedef long long ll;
typedef pair<ll, int> ii;

int par[MAXN];
int label[MAXN], vis[MAXN];
ll minw[MAXN], parw[MAXN];
vector<int> cycle[MAXN];

void dfs(int u, int &m) {
	vis[u] = 1;
	int v = par[u];
	if (vis[v] == 0) dfs(v, m);
	else if (vis[v] == 1) {
		int w = u;
		do {
			cycle[m].push_back(w);
			w = par[w];
		} while(w != u);
		label[v] = m++;
	}
	vis[u] = 2;
	label[u] = label[v];
}

ll boruvka(vector< vector<ii> > adjList) {
	int n = adjList.size();

	printf("graph:\n");
	for(int u = 0; u < n; u++) {
		printf("%d:", u+1);
		for(int i = 0; i < (int)adjList[u].size(); i++) {
			int v = adjList[u][i].second;
			ll w = adjList[u][i].first;
			printf(" %d(%lld)", v+1, w);
		}
		printf("\n");
	}

	ll ans = 0;
	for(int u = 0; u < n; u++)
		par[u] = u, parw[u] = 0;
	while(true) {

		printf("pairs:\n");
		for(int u = 0; u < n; u++) {
			printf("par(%d) = %d,%lld\n", u+1, par[u]+1, parw[u]);
		}

		memset(&vis, 0, sizeof vis);
		int m = 0;
		for(int u = 0; u < n; u++)
			if (vis[u] == 0) dfs(u, m);
		if (m == 1) {
			ll maxw = -INF;
			for(int j = 0; j < (int)cycle[0].size(); j++) {
				int u = cycle[0][j];
				if (parw[u] < maxw) maxw = parw[u];
			}
			return ans - maxw;
		}
		for(int i = 0; i < m; i++) {
			minw[i] = INF;
			for(int j = 0; j < (int)cycle[i].size(); j++) {
				int u = cycle[i][j];
				for(int k = 0; k < (int)adjList[u].size(); k++) {
					ll w = adjList[u][k].first;
					int v = adjList[u][k].second;
					if (i == label[v]) continue;
					if (minw[i] > w - parw[u]) {
						minw[i] = w - parw[u];
					}
				}
			}
			ans += minw[i];
			for(int j = 0; j < (int)cycle[i].size(); j++) {
				int u = cycle[i][j];
				for(int k = 0; k < (int)adjList[u].size(); k++) {
					ll w = adjList[u][k].first;
					int v = adjList[u][k].second;
					if (i == label[v]) continue;
					if (minw[i] == w - parw[u]) {
						minw[i] = INF;
						par[u] = v; parw[u] = w;
					}
				}
			}
			cycle[i].clear();
		}

		/*
		
		
		printf("cycles:\n");
		for(int j = 0; j < m; j++) {
			printf("%d:", j+1);
			for(int u = 0; u < n; u++) {
				if (label[u] != j || !iscycle[u]) continue;
				printf(" %d", u+1);
			}
			printf("\n");
		}
		printf("cur ans: %lld\n\n", ans);*/
	}
}

/*
 * SPOJ MST
 */

#include <cstdio>

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector< vector<ii> > adjList(n);
	while(m --> 0) {
		int u, v;
		ll w;
		scanf("%d %d %lld", &u, &v, &w);
		u--; v--;
		adjList[u].push_back(ii(w, v));
		adjList[v].push_back(ii(w, u));
	}
	printf("%lld\n", boruvka(adjList));
	return 0;
}