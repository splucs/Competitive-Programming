#include <bits/stdc++.h>
using namespace std;
#define MAXN 209

bool vis[MAXN][MAXN];
int adj[MAXN][MAXN], L[MAXN];
int N, K;
set<int> ans;

void dfs(int u, int k) {
	if (vis[u][k]) return;
	vis[u][k] = true;
	if (k == K+1) ans.insert(u);
	else for(int v=1; v<=N; v++) {
		if (adj[u][v] == L[k]) dfs(v, k+1);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%d", &N);
	for(int i=1; i<=N; i++){
		for(int j=1; j<=N; j++){
			scanf("%d", &adj[i][j]);
		}
	}
	scanf("%d", &K);
	for(int k=1; k<=K; k++){
		scanf("%d", &L[k]);
	}
	memset(&vis, false, sizeof vis);
	dfs(1, 1);
	printf("%u\n", ans.size());
	for(set<int>::iterator it = ans.begin(); it!=ans.end(); it++) {
		printf("%d ", *it);
	}
	printf("\n");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}