#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

vector<int> adjList[MAXN], ans[MAXN], dep;
int N, size[MAXN];

int dp(int u, int k) {
	if (k >= int(ans[u].size())) return 1;
	else return ans[u][k];
}

int k;
bool dpcomp(int u, int v) {
	return dp(u, k) > dp(v, k);
}

int dfs(int u, int p) {
	vector<int> adj;
	for(int v : adjList[u]) {
		if (v != p) {
			adj.pb(v);
			dfs(v, u);
		}
	}
	ans[u].resize(adj.size() + 1);
	ans[u][0] = 0;
	for(k = 1; k <= int(adj.size()); k++) {
		dep.clear();
		for(int v : adj) {
			if (ans[v].size() > k) dep.pb(v);
			else break;
		}
		if (dep.size() < k) {
			ans[u][k] = 2;
		}
		else {
			sort(all(dep), dpcomp);
			int minm = N;
			for(int i = 0; i < k; i++) {
				int v = dep[i];
				minm = min(minm, dp(v, k));
			}
			ans[u][k] = minm+1;
		}
		printf("dp[%d][%d] = %d\n", u, k, ans[u][k]);
	}

	adjList[u].swap(adj);
}

int main() {
	scanf("%d", &N);
	FOR(j, N-1) {
		int u, v;
		scanf("%d %d", &u, &v);
		adjList[u].pb(v);
		adjList[v].pb(u);
	}
	ll tot = 0;
	dfs(1, -1);
	FOR1(u, N) {
		for(int r : ans[u]) {
			tot += r;
		}
		tot += N - adjList[u].size();
	}
	printf("%I64d\n", tot);
	return 0;
}