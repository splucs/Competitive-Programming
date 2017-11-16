#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int N, M, p[MAXN], inv[MAXN];
bool adj[MAXN][MAXN];
typedef long long ll;
ll dp[MAXN];

bool comp(int i, int j) {
	if (adj[i][j]) return i > j;
	return i < j;
}

int main() {
	int u, v;
	scanf("%d %d", &N, &M);
	memset(&adj, false, sizeof adj);
	while (M--) {
		scanf("%d %d", &u, &v);
		adj[u][v] = adj[v][u] = true;
	}
	for(int i=0; i<N; i++) inv[i] = i;
	sort(inv, inv+N, comp);
	for(int i=0; i<N; i++) {
		p[inv[i]] = i;
		dp[i] = 0;
	}
	for(int i=0; i<N; i++) {
		if (dp[i] == 0) dp[i] = 1;
		int mx = N+1;
		for(int j=i+1; j<N; j++) {
			if (p[j] < mx && p[j] > p[i]) {
				dp[j] += dp[i];
				mx = p[j];
			}
		}
		if (mx < N+1) dp[i] = 0;
	}
	ll ans = 0;
	for(int i=0; i<N; i++) ans += dp[i];
	printf("%I64d\n", ans);
	return 0;
}