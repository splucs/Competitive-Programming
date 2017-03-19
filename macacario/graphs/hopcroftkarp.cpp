#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#define INF (1<<30)
#define MAXN 1009
using namespace std;

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN], dist[MAXN];
int m, n;

bool bfs()
{
	queue<int> q;
	for (int u = 1; u <= m; u++) {
		if (pairU[u] == 0) {
			dist[u] = 0;
			q.push(u);
		}
		else dist[u] = INF;
	}
	dist[0] = INF;
	int u, v;
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (dist[u] < dist[0]) {
			for (int i = 0; i<(int)adjU[u].size(); ++i) {
				v = adjU[u][i];
				if (dist[pairV[v]] == INF) {
					dist[pairV[v]] = dist[u] + 1;
					q.push(pairV[v]);
				}
			}
		}
	}
	return (dist[0] != INF);
}

bool dfs(int u)
{
	if (u == 0) return true;
	int v;
	for (int i = 0; i != (int)adjU[u].size(); ++i) {
		v = adjU[u][i];
		if (dist[pairV[v]] == dist[u] + 1) {
			if (dfs(pairV[v])) {
				pairV[v] = u; pairU[u] = v;
				return true;
			}
		}
	}
	dist[u] = INF;
	return false;
}

int hopcroftKarp()
{
	memset(&pairU, 0, sizeof pairU);
	memset(&pairV, 0, sizeof pairV);
	int result = 0;
	while (bfs()) {
		for (int u = 1; u <= m; u++) {
			if (pairU[u] == 0 && dfs(u))
				result++;
		}
	}
	return result;
}