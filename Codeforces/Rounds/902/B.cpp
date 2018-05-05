#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

vector<int> adjList[MAXN];
int desired[MAXN], ans;

void dfs(int u, int c) {
	if (c != desired[u]) {
		c = desired[u];
		ans++;
	}
	for(int i = 0; i < (int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		dfs(v, c);
	}
}

int main() {
	int N;
	scanf("%d", &N);
	for(int v = 2, u; v <= N; v++) {
		scanf("%d", &u);
		adjList[u].push_back(v);
	}
	for(int u = 1; u <= N; u++) {
		scanf("%d", &desired[u]);
	}
	ans = 0;
	dfs(1, -1);
	printf("%d\n", ans);
	return 0;
}