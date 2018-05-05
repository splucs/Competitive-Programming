#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR1(i, n) for(int i = 1; i <= n; i++)

vector<int> adjList[MAXN];
list<int> ans[MAXN];

bool dfs(int u, int p) {
	list<int> prev, after;
	int nsons = 0;
	for(int v : adjList[u]) {
		if (v == p) continue;
		if (dfs(v, u)) {
			prev.splice(prev.end(), ans[v]);
		}
		else {
			nsons++;
			after.splice(after.end(), ans[v]);
		}
	}
	ans[u].clear();
	ans[u].splice(ans[u].end(), prev);
	ans[u].push_back(u);
	ans[u].splice(ans[u].end(), after);
	return nsons % 2 != 0;
}

int main() {
	int N;
	scanf("%d", &N);
	FOR1(u, N) {
		int v;
		scanf("%d", &v);
		if (v == 0) continue;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	if (dfs(1, -1)) {
		printf("NO\n");
	}
	else {
		printf("YES\n");
		for(int u : ans[1]) {
			printf("%d\n", u);
		}
	}
	return 0;
}
