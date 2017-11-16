#include <bits/stdc++.h>
using namespace std;
#define MAXN 60
#define INF (1<<30)

int dp[MAXN][MAXN];
int len;
char str[MAXN];

int c2i(char c)
{
	return c - 'a';
}

int DP(int i, int j)
{
	if (dp[i][j] < INF) return dp[i][j];
	if (j == c2i('z') + 1) return dp[i][j] = 0;
	if (i >= len) return dp[i][j] = c2i('z') + 1 - j;
	int ans = INF;
	if (c2i(str[i]) == j) ans = min(ans, DP(i+1, j+1));
	ans = min(ans, 1 + DP(i, j+1));
	ans = min(ans, DP(i+1, j));
	return dp[i][j] = ans;
}

int main()
{
	scanf(" %s", str);

	len = strlen(str);

	for(int i=0; i<MAXN; i++) {
		dp[i][c2i('z')+1] = 0;
		for(int j=0; j<=c2i('z'); j++) {
			dp[i][j] = INF;
		}
	}

	printf("%d\n", DP(0, 0));

	return 0;
}