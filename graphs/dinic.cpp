#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#define INF (1<<30)
#define MAXN 109
using namespace std;

vector<int> adjList[MAXN];
int cap[MAXN][MAXN], dist[MAXN], work[MAXN], N, M;

int dfs(int u, int f, int s, int t) {
	if (u == t) return f;
	int v, df;
	for (int &i = work[u]; i<(int)adjList[u].size(); i++) {
		v = adjList[u][i];
		if (cap[u][v] <= 0) continue;
		if (dist[v] == dist[u] + 1) {
			df = dfs(v, min(f, cap[u][v]), s, t);
			if (df > 0) {
				cap[u][v] -= df;
				cap[v][u] += df;
				return df;
			}
		}
	}
	return 0;
}

bool bfs(int s, int t) {
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	while (!q.empty()) {
		u = q.front(); q.pop();
		for (int i = 0; i<(int)adjList[u].size(); i++) {
			v = adjList[u][i];
			if (dist[v] < 0 && cap[u][v] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[t] >= 0;
}

int dinic(int s, int t) {
	int result = 0, f;
	while (bfs(s, t)) {
		memset(&work, 0, sizeof work);
		while (f = dfs(s, INF, s, t)) result += f;
	}
	return result;
}