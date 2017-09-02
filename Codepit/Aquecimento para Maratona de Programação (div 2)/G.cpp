#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define UNVISITED -1
#define MOD 1000000007

int num[MAXN], vis[MAXN], component[MAXN], N, M, s, t, low[MAXN], counter, root, numSCC;
stack<int> S;
vector<int> adjList[MAXN];

void dfs(int u) {
	low[u] = num[u] = counter++;
	S.push(u);
	vis[u] = 1;
	int v;
	for (int j = 0; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (num[v] == UNVISITED) dfs(v);
		if (vis[v]) low[u] = min(low[u], low[v]);
	}
	if (low[u] == num[u]) {
		while (true) {
			v = S.top(); S.pop(); vis[v] = 0;
			component[v] = numSCC;
			if (u == v) break;
		}
		numSCC++;
	}
}

void tarjan(){
	counter = numSCC = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&vis, 0, sizeof vis);
	memset(&low, 0, sizeof low);
	for (int i = 1; i <= N; i++){
		if (num[i] == UNVISITED)
			dfs(i);
	}
}

set<int> adjCompS[MAXN];
int dp[MAXN];

int DP(int u) {
	if (dp[u] >= 0) return dp[u];
	if (component[t] == u) return dp[u] = 1;
	dp[u] = 0;
	for(set<int>::iterator it = adjCompS[u].begin(); it != adjCompS[u].end(); it++) {
		int v = *it;
		dp[u] += DP(v);
		dp[u] %= MOD;
	}
	return dp[u];
}

int main() {
	int u, v;
	scanf("%d %d %d %d", &N, &M, &s, &t);
	while(M-->0) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
	}
	tarjan();
	for(u=1; u<=N; u++) {
		for(int i=0; i<(int)adjList[u].size(); i++) {
			v = adjList[u][i];
			if (component[u] != component[v])
				adjCompS[component[u]].insert(component[v]);
		}
	}
	memset(&dp, -1, sizeof dp);
	printf("%d\n", DP(component[s]));
	return 0;
}