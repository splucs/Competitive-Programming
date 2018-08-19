#include <bits/stdc++.h>
using namespace std;

#define FOR(i, N) for (int i = 0; i < N; ++i)
#define MAXN 300009
#define pb push_back
typedef long long int ll;
typedef pair<int, int> ii;
const int INF = 1e9 + 1;

int N, M, K, cnt[MAXN] = {}, vis[MAXN] = {};
vector<int> g[MAXN];
vector<ii> sol;

int dfs(int u){
	vis[u] = 1;
	int qty = cnt[u];
	for (auto v : g[u]){
		if (!vis[v]) {
			if (dfs(v)) {sol.pb(ii(u + 1, v + 1)); qty++;}
		}
	}
	return qty & 1;
}

int main() {
	scanf("%d%d%d", &N, &M, &K);
	int a, b;
	FOR(i, M){
		scanf("%d%d", &a, &b); --a, --b;
		cnt[a]++, cnt[b]++;
	}
	FOR(i, N) cnt[i] &= 1;
	FOR(i, K){
		scanf("%d%d", &a, &b); --a, --b;
		g[a].pb(b), g[b].pb(a);
	}
	bool poss = true;
	FOR(i, N)if (!vis[i]) {
		poss = poss && (!dfs(i));
		if (!poss) break;
	}
	printf("%s\n", poss? "YES" : "NO");
	if (poss){
		printf("%d\n", sol.size());
		for (auto it : sol){
			printf("%d %d\n", it.first, it.second);
		}
	}
}