#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int cnt, c[MAXN][2], N;
vector<int> adjList[MAXN];

void dfs(int u, int p, int pc) {
	c[u][0] = ++cnt;
	c[u][1] = pc;
	for(int i=0, j=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v == p) continue;
		dfs(v, u, c[u][j%2]);
		j++;
	}
	if (adjList[u].size() == 1u && p != -1) {
		c[u][0] = c[p][0] + c[p][1] - pc;
	}
}

int main() {
	scanf("%d", &N);
	for(int u, v, i = 1; i<N; i++) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	cnt = 0;
	dfs(1, -1, ++cnt);
	for(int i=1; i<=N; i++) {
		printf("%d %d\n", c[i][0], c[i][1]);
	}
	return 0;
}