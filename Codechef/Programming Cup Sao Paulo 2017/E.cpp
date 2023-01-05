#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

typedef long long ll;
typedef pair<ll, int> ii;
int N;
vector<ii> adjList[MAXN];
ll size[MAXN], E[MAXN], ans, C;

int dfs(int u, int p, ll pw) {
	size[u] = E[u];
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].second;
		ll w = adjList[u][i].first;
		if (v == p) continue;
		size[u] += dfs(v, u, w);
	}
	ll m;
	if (size[u] % C == 0) m = size[u]/C;
	else m = size[u]/C + 1;
	ans += m*2*pw;
	return size[u];
}

int main() {
	int u, v;
	ll w;
	scanf("%d %lld", &N, &C);
	for(u=1; u<=N; u++) scanf("%lld", &E[u]);
	for(int j=1; j<N; j++) {
		scanf("%d %d %lld", &u, &v, &w);
		adjList[u].push_back(ii(w, v));
		adjList[v].push_back(ii(w, u));
	}
	ans = 0;
	dfs(1, -1, 0);
	printf("%lld\n", ans);
	return 0;
}