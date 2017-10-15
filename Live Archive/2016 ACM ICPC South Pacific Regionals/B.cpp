#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

int N, L, R, x[MAXN], y[MAXN], cnt;
typedef pair<int, int> ii;
vector<ii> adjList[MAXN];

void dfs(int u, int uver) {
	if (cnt >= L && cnt < R) {
		printf("%d ", u);
	}
	cnt++;
	if (cnt > R) return;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].second;
		int vver = adjList[u][i].first;
		if (vver <= uver) break;
		dfs(v, vver);
	}
}

int main() {
	while(scanf("%d %d %d", &N, &L, &R) != EOF) {

		for(int i=1; i<=N; i++) {
			scanf("%d %d", &x[i], &y[i]);
		}
		for(int i=0; i<MAXN; i++) adjList[i].clear();
		for(int i = N; i > 0; i--) {
			adjList[x[i]].push_back(ii(i, y[i]));
		}
		
		cnt = 0;
		while(cnt < R) dfs(0, 0);
		printf("\n");
		
		
	}
	return 0;
}