#include <bits/stdc++.h>
using namespace std;
#define MAXN 60

int main()
{
	int dp[MAXN][2], vet[MAXN], n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &vet[i]);
	}
	int ans = 1;
	for (int i = 0; i < n; i++) {
		dp[i][0] = dp[i][1] = 1;
		for (int j = 0; j < i; j++) {
			if (vet[j] > vet[i]) dp[i][0] = max(dp[i][0], 1 + dp[j][1]);
			if (vet[j] < vet[i]) dp[i][1] = max(dp[i][1], 1 + dp[j][0]);
			ans = max(ans, max(dp[i][0], dp[i][1]));
		}
	}
	printf("%d\n", ans);
	return 0;
}