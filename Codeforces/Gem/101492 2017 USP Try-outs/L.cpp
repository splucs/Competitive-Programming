#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000002
#define MAXM 102

int N, M, K;
char T[MAXN], P[MAXM], dp[MAXN][MAXM];

int main() {
	
	scanf("%d %d %d %s %s", &M, &N, &K, P, T);
	
	
	for(int i=N; i>=0; i--) {
		for(int j=M; j>=0; j--) {
			if (j == M) dp[i][j] = 0;
			else if (i == N) {
				dp[i][j] = 1 + dp[i][j+1];
			}
			else {
				dp[i][j] = K+1;
				if (T[i] == P[j] && dp[i+1][j+1] < dp[i][j]) dp[i][j] = dp[i+1][j+1];
				if (dp[i][j] > 1 + dp[i+1][j]) dp[i][j] = 1 + dp[i+1][j];
				if (dp[i][j] > 1 + dp[i][j+1]) dp[i][j] = 1 + dp[i][j+1];
				if (dp[i][j] > 1 + dp[i+1][j+1]) dp[i][j] = 1 + dp[i+1][j+1];
			}
			if (dp[i][j] > K) dp[i][j] = K+1;
		}
	}
	
	bool ok = false;
	for(int i=0; i<=N; i++) {
		if (dp[i][0] <= K) ok = true;
	}
	if (ok) printf("S\n");
	else printf("N\n");
	
	return 0;
}