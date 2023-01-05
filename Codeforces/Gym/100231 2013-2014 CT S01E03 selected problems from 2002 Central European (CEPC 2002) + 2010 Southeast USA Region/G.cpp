#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1<<30)

vector<int> to[MAXN], dep[MAXN], arr[MAXN], dp[MAXN];
typedef pair<int, int> ii;
vector<ii> ans;
int N, done[MAXN];

int DP(int u, int i) {
	if (dp[u][i] >= 0) return dp[u][i];
	dp[u][i] = INF;
	if (i+1 < (int)to[u].size()) dp[u][i] = min(DP(u, i+1), dp[u][i]);
	if (u == N) dp[u][i] = min(dep[u][i], dp[u][i]);
	int v = to[u][i];
	if (v == N) dp[u][i] = min(arr[u][i], dp[u][i]);
	int n = to[v].size();
	int lo = -1;
	int hi = n;
	while(hi > lo + 1) {
		int mid = (hi + lo) / 2;
		if (dep[v][mid] >= arr[u][i]) hi = mid;
		else lo = mid;
	}
	if (hi < n) dp[u][i] = min(dp[u][i], DP(v, hi));
	return dp[u][i];
}

int main() {
	scanf("%d", &N);
	int M, deph, depm, arrh, arrm, v;
	for(int u=1; u<=N; u++) {
		scanf("%d", &M);
		dp[u].assign(M, -1);
		while(M --> 0) {
			scanf("%d:%d %d:%d %d", &deph, &depm, &arrh, &arrm, &v);
			to[u].push_back(v);
			dep[u].push_back(deph*60 + depm);
			arr[u].push_back(arrh*60 + arrm);
		}
	}
	int n = to[1].size();
	for(int i=0; i<n; i++) {
		if (i+1 < n && DP(1, i) >= DP(1, i+1)) continue;
		if (DP(1, i) == INF) continue;
		if (!ans.empty() && ans.back().first == dep[1][i]) continue;
		ans.push_back(ii(dep[1][i], DP(1, i)));
	}
	printf("%u\n", ans.size());
	for(int i=0; i<(int)ans.size(); i++) {
		printf("%02d:%02d %02d:%02d\n", ans[i].first/60, ans[i].first%60, ans[i].second/60, ans[i].second%60);
	}
	return 0;
}