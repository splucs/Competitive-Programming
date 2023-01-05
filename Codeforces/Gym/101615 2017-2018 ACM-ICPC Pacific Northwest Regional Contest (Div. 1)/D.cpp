#include <bits/stdc++.h>
#define MAXN 100009
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define pb push_back
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
using namespace std;
typedef pair<int,int> ii;

vector<ii> adj[MAXN];
int par[MAXN], total[MAXN];

bool marked[MAXN];
set<ii> vis;

vector<int> ans;

void dfs(int u, int p) {
	par[u] = p;

	int c, v;	
	FOR(i, sz(adj[u])) {
		tie(c, v) = adj[u][i];
		if (v == p) continue;
		dfs(v, u);
	}
	return;
}

void dfs2(int u, int p, int t) {
	t += total[u];
	if (t > 0) marked[u] = true;

	int c, v;
	FOR(i, sz(adj[u])) {
		tie(c, v) = adj[u][i];
		if (v == p) continue;
		dfs2(v, u, t);
	}
	return;
}

int main() {
	int n, a, b, c;
	scanf("%d", &n);
	FOR(i, n-1) {
		scanf("%d %d %d", &a, &b, &c);
		adj[a].pb(ii(c, b));
		adj[b].pb(ii(c, a));
	}

	dfs(1, -1);
	FOR1(i, n) {
		sort(all(adj[i]));
		FOR(j, sz(adj[i]) - 1) {
			if (adj[i][j].first == adj[i][j+1].first) {
				a = adj[i][j].second, b = adj[i][j+1].second;
				if (a != par[i]) total[a]++;
				if (b != par[i]) total[b]++;
				if (a == par[i] || b == par[i]) {
					total[1]++;
					total[i]--;
				}
			}
		}
	}
	dfs2(1, -1, 0);

	int cnt = 0;
	FOR1(i, n) if (!marked[i]) cnt++;

	printf("%d\n", cnt);
	FOR1(i, n) {
		if (!marked[i]) printf("%d\n", i);
	}
}