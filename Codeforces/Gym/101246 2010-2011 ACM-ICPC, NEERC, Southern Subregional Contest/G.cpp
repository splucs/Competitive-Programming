#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define UNVISITED -1

int num[MAXN], vis[MAXN], component[MAXN], N, M, low[MAXN], counter, root, numSCC;
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

int cnt[MAXN], w;

int tarjan(){
	counter = numSCC = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&vis, 0, sizeof vis);
	memset(&low, 0, sizeof low);
	for (int i = 0; i < N; i++){
		if (num[i] == UNVISITED)
			dfs(i);
	}
	memset(&cnt, 0, sizeof cnt);
	int ans = 0;
	for (int i = 0; i < N; i++){
		cnt[component[i]]++;
		ans = max(ans, cnt[component[i]]);
	}
	return ans;
}

int eu[20009], ev[20009];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int u, v, curw;
	scanf("%d %d", &N, &M);
	for(int j=1; j<=M; j++) {
		scanf("%d %d", &u, &v);
		u--;
		v--;
		eu[j] = u;
		ev[j] = v;
		adjList[u].push_back(v);
	}
	vector<int> ans;
	w = 0;
	for(int j=1; j<=M; j++){
		u = ev[j];
		v = eu[j];
		adjList[u].push_back(v);
		curw = tarjan();
		adjList[u].pop_back();
		if (curw > w){
			w = curw;
			ans.clear();
		}
		if (curw == w) ans.push_back(j);
	}
	printf("%d\n%u\n", w, ans.size());
	for(int i=0; i<(int)ans.size(); i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}