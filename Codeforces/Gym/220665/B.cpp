#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

int g[MAXN], dp[MAXN][10];

int digitProduct(int n) {
	int ans = 1;
	while(n > 0) {
		int p = n % 10;
		n /= 10;
		if (p) ans *= p;
	}
	return ans;
}

int main() {
	for(int i = 1; i < MAXN; i++) {
		if (i < 10) g[i] = i;
		else g[i] = g[digitProduct(i)];
	}

	for(int j = 1; j <= 9; j++) dp[0][j] = 0;

	for(int i = 1; i < MAXN; i++) {
		for(int j = 1; j <= 9; j++) {
			dp[i][j] += dp[i-1][j];
		}
		dp[i][g[i]]++;
	}

	int Q, l, r, k;
	scanf("%d", &Q);
	while(Q --> 0) {
		scanf("%d %d %d", &l, &r, &k);
		printf("%d\n", dp[r][k] - dp[l-1][k]);
	}

	return 0;
}