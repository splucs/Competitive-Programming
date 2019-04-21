#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 100009
#define MAXLOGN 20
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;

int dp[MAXN][2][2];
int l[MAXN], r[MAXN], status[MAXN];

int nand(int b1, int b2) {
	return 1^(b1 & b2);
}

int DP(int u, int i, int j) {
	int &ans = dp[u][i][j];
	if (ans >= 0) return ans;
	if (u == 0) return ans = (i == j);

	if (status[u] == 0 && j == 1) return ans = 0;
	if (status[u] == 1 && j == 0) return ans = 0;
	
	ans = 0;
	FOR(i1, 2) FOR(j1, 2) FOR(i2, 2) FOR(j2, 2) {
		if (nand(i1, i2) != i) continue;
		if (status[u] == -1 && nand(j1, j2) != j) continue;
		int lres = DP(l[u], i1, j1);
		int rres = DP(r[u], i2, j2);
		ans = (ans + lres*1ll*rres) % MOD;
	}
	return ans;
}

int main() {
	int n;
	scanf("%d", &n);
	FOR1(u, n) {
		scanf("%d %d %d", &l[u], &r[u], &status[u]);
	}
	FOR(u, MAXN) FOR(i, 2) FOR(j, 2) dp[u][i][j] = -1;
	int ans = (DP(1, 1, 0) + DP(1, 0, 1)) % MOD;
	printf("%d\n", ans);
	return 0;
}