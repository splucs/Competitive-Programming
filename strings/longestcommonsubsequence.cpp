#include <cstdio>
#define MAXN 109

int dp[MAXN][MAXN], n, m;
char str1[MAXN], str2[MAXN];

int DP(int i, int j) {
	if (dp[i][j] >= 0) return dp[i][j];
	if (i == n && j == m) return dp[i][j] = 0;
	if (i == n) return dp[i][j] = DP(i, j + 1);
	if (j == m) return dp[i][j] = DP(i + 1, j);
	dp[i][j] = DP(i + 1, j);
	if (DP(i, j + 1)>dp[i][j]) dp[i][j] = dp[i][j + 1];
	if (str1[i] == str2[j] && 1 + DP(i + 1, j + 1)>dp[i][j])
		dp[i][j] = 1 + dp[i + 1][j + 1];
	return dp[i][j];
}