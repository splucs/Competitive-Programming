#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int bff[MAXN], cycle[MAXN], vis[MAXN];
vector<int> adj[MAXN];

void processcycle(int u){
	//printf("processing cycle starting from %d\n", u);
	int sz = 1, v = bff[u];
	while(v != u){
		sz++;
		v = bff[v];
	}
	cycle[u] = sz;
	v = bff[u];
	while(v != u){
		cycle[v] = sz;
		v = bff[v];
	}
}

void dfs(int u){
	if (vis[u] > 0) return;
	vis[u] = 1;
	
	int v = bff[u];
	cycle[u] = 0;
	dfs(v);
	if (vis[v] == 1){
		processcycle(v);
	}
	
	vis[u] = 2;
}

int dfs2(int u){
	int ans = 1;
	for(int i=0; i<(int)adj[u].size(); i++){
		int v = adj[u][i];
		if (bff[u] == v) continue;
		ans = max(ans, 1+dfs2(v));
	}
	return ans;
}

int main()
{
	int T, n, ans, sum;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo<=T; caseNo++){
		scanf("%d", &n);
		memset(&vis, 0, sizeof vis);
		ans = sum = 0;
		for(int i=1; i<=n; i++) adj[i].clear();
		for(int i=1; i<=n; i++){
			scanf("%d", &bff[i]);
			adj[bff[i]].push_back(i);
		}
		for(int i=1; i<=n; i++){
			if (vis[i] == 0){
				dfs(i);
			}
			ans = max(ans, cycle[i]);
			//printf("cycle[%d] = %d\n", i, cycle[i]);
		}
		//printf("maxcycle = %d\n", ans);
		for(int i=1; i<=n; i++){
			if (cycle[i] == 2) sum += dfs2(i);
		}
		ans = max(sum, ans);
		printf("Case #%d: %d\n", caseNo, ans);
	}
	return 0;
}