#include <vector>
#include <queue>
#include <cstring>
#define INF 0x3f3f3f3f
#define MAXN 1009
using namespace std;

/*
 * Hopcroft-Karp's Algorithm O(E*sqrt(V))
 */

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN], dist[MAXN];
int m, n;
//Vertices enumerados de 1 a m em U e de 1 a n em V!!!!

bool bfs() {
	queue<int> q;
	for (int u = 1; u <= m; u++) {
		if (pairU[u] == 0) {
			dist[u] = 0; q.push(u);
		}
		else dist[u] = INF;
	}
	dist[0] = INF;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (dist[u] >= dist[0]) continue;
		for (int i = 0; i < (int)adjU[u].size(); i++) {
			int v = adjU[u][i];
			if (dist[pairV[v]] == INF) {
				dist[pairV[v]] = dist[u] + 1;
				q.push(pairV[v]);
			}
		}
	}
	return (dist[0] != INF);
}

bool dfs(int u) {
	if (u == 0) return true;
	for (int i = 0; i < (int)adjU[u].size(); i++) {
		int v = adjU[u][i];
		if (dist[pairV[v]] == dist[u]+1) {
			if (dfs(pairV[v])) {
				pairV[v] = u; pairU[u] = v;
				return true;
			}
		}
	}
	dist[u] = INF;
	return false;
}

int hopcroftKarp() {
	memset(&pairU, 0, sizeof pairU);
	memset(&pairV, 0, sizeof pairV);
	int result = 0;
	while (bfs()) {
		for (int u=1; u<=m; u++) {
			if (pairU[u]==0 && dfs(u))
				result++;
		}
	}
	return result;
}

/*
 * Codeforces 101712A
 */

#include <cstdio>

int main() {
	scanf("%d %d", &m, &n);
	for (int u = 1; u <= m; u++) {
		int v;
		while(scanf("%d", &v), v) adjU[u].push_back(v);
	}
	printf("%d\n", hopcroftKarp());
	for (int u = 1; u <= m; u++) {
		if (pairU[u]) printf("%d %d\n", u, pairU[u]);
	}
	return 0;
}