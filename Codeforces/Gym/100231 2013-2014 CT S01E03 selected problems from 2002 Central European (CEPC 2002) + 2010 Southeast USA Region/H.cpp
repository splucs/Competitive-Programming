#include <bits/stdc++.h>
using namespace std;
#define MAXN 102
#define INF (1<<30)

int N, M;
int dp[MAXN][MAXN][MAXN][2];

int main() {
	scanf("%d %d", &N, &M);
	for(int s=0; s<=N; s++) {
		for(int c=0; c<=s; c++) {
			for(int i=0; i+c<=s; i++) {
				int j = s-i-c;
				
				//player 0
				if (c == 0) dp[c][i][j][0] = dp[i][0][0][0] - j;
				else {
					dp[c][i][j][0] = -INF;
					for(int k=1; k <= M && k <= c; k++) {
						dp[c][i][j][0] = max(dp[c][i][j][0], dp[c-k][i+k][j][1]);
					}
				}
				
				//player 1
				if (c == 0) dp[c][i][j][1] = dp[j][0][0][1] + i;
				else {
					dp[c][i][j][1] = INF;
					for(int k=1; k <= M && k <= c; k++) {
						dp[c][i][j][1] = min(dp[c][i][j][1], dp[c-k][i][j+k][0]);
					}
				}
			}
		}
	}
	printf("%d\n", (dp[N][0][0][0] + N)/2);
	return 0;
}