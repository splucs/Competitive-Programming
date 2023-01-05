#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF (1<<30)

int label[MAXN], numCastle, N, inv[MAXN];
vector<int> adjList[MAXN], component[MAXN];

bool readCastle(int num) {
	int n, m, w;
	if(scanf("%d %d %d", &n, &m, &w) == EOF) return false;
	//printf("castle %d,%d,%d\n", n, m, w);
	for(int j=0, u, v; j<m; j++) {
		scanf("%d %d", &u, &v);
		N = max(N, max(u, v));
		label[u] = label[v] = num;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	for(int i=0, u, v; i<w; i++) {
		scanf("%d %d", &u, &v);
		N = max(N, max(u, v));
		label[u] = num;
		label[v] = ++numCastle;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
		readCastle(label[v]);
	}
	return true;
}

int dp[MAXN][2];

int DP(const int n, const int p) {
	if (dp[n][p] >= 0) return dp[n][p];
	
	int ans = INF;
	for(int mask=0; mask<(1<<component[label[n]].size()); mask++) {
		int cur = 0;
		bool ok = true;
		for(int i=0; i<(int)component[label[n]].size() && ok; i++) {
			int u = component[label[n]][i];
			if (mask & (1<<i)) cur++;
			for(int j=0; j<(int)adjList[u].size() && ok; j++) {
				int v = adjList[u][j];
				if (label[v] > label[u] && (mask & (1<<i))) cur += DP(v, 1);
				if (label[v] > label[u] && !(mask & (1<<i))) cur += DP(v, 0);
				if (label[v] < label[u] && !p && !(mask & (1<<i))) ok = false;
				if (label[v] == label[u] && !(mask & (1<<i)) && !(mask & (1<<inv[v]))) ok = false;
			}
		}
		if (ok) ans = min(ans, cur);
	}
	for(int i=0; i<(int)component[label[n]].size(); i++) {
		int u = component[label[n]][i];
		dp[u][p] = ans;
	}
	//printf("dp[%d][%d] = %d\n", label[n], p, ans);
	return ans;
}

int main() {
	N=0, numCastle=1;
	while(readCastle(numCastle)) {
		
		for(int i=1; i<=N; i++) {
			inv[i] = component[label[i]].size();
			component[label[i]].push_back(i);
		}
		
		memset(&dp, -1, sizeof dp);
		int ans = DP(component[1].front(), 0);
		printf("%d\n", ans);
		
		for(int i=1; i<=N; i++) adjList[i].clear();
		for(int i=1; i<=numCastle; i++) {
			component[i].clear();
		}
		N=0, numCastle=1;
	}
	
	return false;
}