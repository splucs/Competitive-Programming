#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 109
#define INF 1e+18

int arr[MAXN], lis[MAXM];
double price[MAXN], dp[MAXN][MAXM];

int main() {
	int N, M;
	while(scanf("%d %d", &M, &N), N&&M) {
		for(int i=0; i<M; i++) scanf("%d", &lis[i]);
		for(int i=0; i<N; i++) scanf("%d %lf", &arr[i], &price[i]);
		for(int i=0; i<=N; i++) dp[i][M] = 0;
		for(int j=0; j<M; j++) dp[N][j] = INF;
		for(int i=N-1; i>=0; i--) {
			for(int j=M-1; j>=0; j--) {
				if (arr[i] == lis[j]) dp[i][j] = min(dp[i+1][j], price[i] + dp[i+1][j+1]);
				else dp[i][j] = dp[i+1][j];
			}
		}
		if (dp[0][0] > 1e+12) printf("Impossible\n");
		else printf("%.2f\n", dp[0][0]);
	}
	return 0;
}