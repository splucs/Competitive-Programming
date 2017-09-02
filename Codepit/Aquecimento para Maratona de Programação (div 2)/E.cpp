#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MOD 1300031LL

typedef long long ll;
typedef pair<int, ll> ii;
vector<ii> adjList[MAXN];
ll ans;
int size[MAXN], N;

int sizedfs(int u, int p) {
	size[u] = 1;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		if (v == p) continue;
		size[u] += sizedfs(v, u);
	}
	return size[u];
}

void dfs(int u, int p) {
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		ll w = adjList[u][i].second;
		if (v == p) continue;
		dfs(v, u);
		ans += w*(size[v]*(N-size[v]))%MOD;
		ans %= MOD;
	}
}

int main() {
	int T, u, v;
	ll w;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=1; i<=N; i++) adjList[i].clear();
		for(int i=1; i<N; i++) {
			scanf("%d %d %lld", &u, &v, &w);
			adjList[u].push_back(ii(v, w));
			adjList[v].push_back(ii(u, w));
		}
		ans = 0;
		sizedfs(1, -1);
		dfs(1, -1);
		printf("%lld\n", ans);
	}
	return 0;
}