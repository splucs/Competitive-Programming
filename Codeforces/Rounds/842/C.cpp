#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

vector<int> getDivisors(int n) {
	vector<int> ans;
	for (int i=1; i*i <= n; i++) {
		if (n%i == 0) {
			ans.push_back(i);
			if (i*i != n) ans.push_back(n/i);
		}
	}
	return ans;
}

int freq[MAXN], a[MAXN], ans[MAXN], N;
vector<int> adjList[MAXN];

void dfs(int u, int p, int h) {
	vector<int> div = getDivisors(a[u]);
	int nocut = 1;
	for(int i=0; i<(int)div.size(); i++) {
		int val = div[i];
		freq[val]++;
		if (freq[val] >= h-1) ans[u] = max(ans[u], val);
		if (freq[val] == h) nocut = max(nocut, val);
	}
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v == p) continue;
		ans[v] = max(ans[v], nocut);
		dfs(v, u, h+1);
	}
	for(int i=0; i<(int)div.size(); i++) {
		int val = div[i];
		freq[val]--;
	}
}

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N; i++) {
		scanf("%d", &a[i]);
		ans[i] = 1;
	}
	int u, v;
	for(int j=1; j<N; j++) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	dfs(1, -1, 1);
	for(int i=1; i<=N; i++) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}