#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

vector<int> adjList[MAXN];
typedef pair<int, double> ii;
ii dp[MAXN][2];
double arr[MAXN];

ii operator +(ii a, ii b) {
	return ii(a.first + b.first, a.second + b.second);
}

ii dfs(const int u, const int b, const int p) {
	if (dp[u][b].first >= 0) return dp[u][b];
	
	ii ans = ii(0, 0);
	ii cur = ii(0, 0);
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v == p) continue;
		cur = cur + dfs(v, 0, u);
	}
	ans = max(ans, cur);
	
	if (b == 0) {
		for(int j=0; j<(int)adjList[u].size(); j++) {
			int pr = adjList[u][j];
			if (pr == p) continue;
			cur = dfs(pr, 1, u) + ii(1, min(arr[u], arr[pr]));
			//printf("matching %d with %d initial: (%d,%.3f)\n", u, pr, cur.first, cur.second);
			for(int i=0; i<(int)adjList[u].size(); i++) {
				int v = adjList[u][i];
				if (v == p || v == pr) continue;
				cur = cur + dfs(v, 0, u);
				//printf("matching %d with %d now: (%d,%.3f)\n", u, pr, cur.first, cur.second);
			}
			ans = max(ans, cur);
		}
	}
	
	//printf("dp[%d][%d] = (%d,%.3f)\n", u, b, ans.first, ans.second);
	return dp[u][b] = ans;
}

map<string, int> x2id;
int xcnt = 0;
int reduce(string x) {
	if (!x2id.count(x)) {
		x2id[x] = ++xcnt;
		dp[xcnt][0] = dp[xcnt][1] = ii(-1, -1);
		//printf("%s -> %d\n", x.c_str(), xcnt);
	}
	return x2id[x];
}

char buffer[MAXN];

int main() {
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf(" %s", buffer);
		int u = reduce(string(buffer));
		scanf(" %lf", &arr[u]);
		scanf(" %s", buffer);
		int p = reduce(string(buffer));
		adjList[p].push_back(u);
	}
	
	ii ans = dfs(reduce("CEO"), 1, -1);
	
	printf("%d %.8f\n", ans.first, ans.second/ans.first);
	
	return 0;
}