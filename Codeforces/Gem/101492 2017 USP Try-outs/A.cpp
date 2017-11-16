#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define FOR(x,n) for(int x = 0; x < n; x++)
char word[1000009];

bool visited[MAXN];
int cor[MAXN];
vector<vector<int> > viz;

bool dfs(int n, int c, int k) {
	visited[n] = true; cor[n] = c;
	for (int i = 0; i < viz[n].size(); i++) {
		int v = viz[n][i];
		if (visited[v] && cor[v] == c) return false;
		if (!visited[v] && !dfs(v, (c+1)%k, k)) return false;
	}
	
	return true;
}

int main() {
	int n, m, k, a, b;
	scanf("%d %d %d", &n, &m, &k);
	viz.resize(n+5);
	
	FOR(x, m) {
		scanf("%d %d", &a, &b);
		a--; b--;
		viz[a].push_back(b);
		viz[b].push_back(a);
	}
	
	memset(visited, 0, sizeof(visited));
	bool ok = true;
	FOR(x, n) {
		if (!visited[x] && !dfs(x, 0, k)) {
			ok = false; break;
		}
	}
	if (!ok) printf("-1\n");
	else {
		FOR(x, n) {
			printf("%d\n", cor[x]+1);
		}
	}
}