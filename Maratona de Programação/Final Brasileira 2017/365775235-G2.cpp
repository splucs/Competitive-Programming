#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF 1000000007

typedef long long ll;
ll dp[MAXN][2];
int l[MAXN], r[MAXN], b[MAXN], size[MAXN];

ll exp(int n){
	if (n==0)return 1;
	ll u = exp(n/2);
	if (n%2==0)return (u*u)%INF;
	return (2*u*u)%INF;
}

int getsize(int u) {
	if (u == 0) return 1;
	if (size[u] > 0) return size[u];
	return size[u] = getsize(l[u]) + getsize(r[u]);
}

ll DP(int u, int k) {
	if (dp[u][k] >= 0) return dp[u][k];
	
	if (u == 0) return 1;
	/*if (b[u] != -1) {
		if (b[u] == k) dp[u][k] = exp(getsize(u));
		else dp[u][k] = 0;
	}
	else {*/
		if (k == 0) {
			 dp[u][k] = (DP(l[u], 1)*DP(r[u], 1)) % INF;
		}
		else {
			dp[u][k] = ((DP(l[u], 1)*DP(r[u], 0)) % INF + (DP(l[u], 0)*DP(r[u], 0)) % INF + (DP(l[u], 0)*DP(r[u], 1)) % INF) % INF;
		}
	//}
	//printf("dp[%d][%d] = %lld\n", u, k, dp[u][k]);
	return dp[u][k];
}

ll solve(int u) {
	if (u == 0) return 1;
	if (b[u] != -1) {
		ll ans = 0;
		if (b[u] != 0) {
			ans = (DP(l[u], 1)*DP(r[u], 1)) % INF;
		}
		else {
			ans = ((DP(l[u], 1)*DP(r[u], 0)) % INF + (DP(l[u], 0)*DP(r[u], 0)) % INF + (DP(l[u], 0)*DP(r[u], 1)) % INF) % INF;
		}
		//printf("ans[%d] = %lld\n", u, ans);
		return  ans;
	}
	else return (solve(l[u])*solve(r[u]))%INF;
}


int main() {
	int N;
	scanf("%d", &N);
	for(int i=1; i<=N; i++) {
		scanf("%d %d %d", &l[i], &r[i], &b[i]);
	}
	
	memset(&dp, -1, sizeof dp);
	memset(&size, 0, sizeof size);
	ll ans = solve(1);
	
	printf("%lld\n", ans);
	return 0;
	
}
