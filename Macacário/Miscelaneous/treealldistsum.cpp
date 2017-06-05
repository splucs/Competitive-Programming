#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
#define MAXN 10009
#define MOD 1300031

typedef long long ll;
typedef pair<ll, int> ii;
vector<ii> adjList[MAXN];
int N, size[MAXN];

ll dfs(int u, ll pw, int par){
	size[u] = 1;
	int v; ll w, ans = 0;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		w = adjList[u][i].first;
		v = adjList[u][i].second;
		if(v == par) continue;
		ans += dfs(v, w, u);
		size[u] += size[v];
	}
	return (ans + ((size[u]*pw)%MOD)*(N-size[u])) % MOD;
}

/*
 *	URI 2103
 */

int main()
{
	int T, u, v;
	ll w;
	scanf("%d", &T);
	while(T-->0){
		scanf("%d", &N);
		for(int i=0; i<N; i++) adjList[i].clear();
		for(int i=1; i<N; i++){
			scanf("%d %d %lld", &u, &v, &w);
			u--; v--;
			adjList[u].push_back(ii(w, v));
			adjList[v].push_back(ii(w, u));
		}
		printf("%lld\n", dfs(1, 0, -1));
	}
	return 0;
}