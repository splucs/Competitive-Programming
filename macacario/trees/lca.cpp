#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
#define MAXN 100009
#define MAXLOGN 20

typedef pair<int, int> ii;
vector<ii> adjList[MAXN];
int depth[MAXN], level[MAXN];
int P[MAXN][MAXLOGN], N;

void depthdfs(int u) {
	for (int i = 0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		int w = adjList[u][i].second;
		if (v == P[u][0]) continue;
		P[v][0] = u;
		level[v] = 1 + level[u];
		depth[v] = w + depth[u];
		depthdfs(v);
	}
}
void computeP(int root) {
	level[root] = depth[root] = 0;
	P[root][0] = root;
	depthdfs(root);
	for (int j = 1; j < MAXLOGN; j++)
		for (int i = 1; i <= N; i++)
			P[i][j] = P[P[i][j - 1]][j - 1];
}
int LCA(int a, int b) {
	if (level[a] > level[b]) swap(a, b);
	int d = level[b] - level[a];
	for (int i = 0; i<MAXLOGN; i++) {
		if ((d & (1 << i)) != 0) b = P[b][i];
	}
	if (a == b) return a;
	for (int i = MAXLOGN - 1; i >= 0; i--)
		while (P[a][i] != P[b][i]) {
			a = P[a][i]; b = P[b][i];
		}
	return P[a][0];
}
int dist(int u, int v) {
	return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}