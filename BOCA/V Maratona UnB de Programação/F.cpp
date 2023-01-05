#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define MAXM 69

int arr[MAXN];
int dp[MAXN][MAXM][MAXM], A[MAXN][MAXM][MAXM];

int main() {
	int M, N;
	
	while(scanf("%d %d", &M, &N) != EOF) {
		for(int i=1; i<=N; i++) {
			scanf("%d", &arr[i]);
		}
		
		for(int i=N+1; i>0; i--) {
			for(int j=0; j<=M; j++) {
				for(int k=0; k<=M; k++) {
					if (i == N+1) {
						dp[i][j][k] = 0;
						A[i][j][k] = -1;
					}
					else {
						dp[i][j][k] = dp[i+1][j][k];
						A[i][j][k] = -1;
						if (j >= arr[i] && dp[i][j][k] < dp[i+1][j-arr[i]][k] + 1) {
							dp[i][j][k] = dp[i+1][j-arr[i]][k] + 1;
							A[i][j][k] = 1;
						}
						if (k >= arr[i] && dp[i][j][k] < dp[i+1][j][k-arr[i]] + 1) {
							dp[i][j][k] = dp[i+1][j][k-arr[i]] + 1;
							A[i][j][k] = 2;
						}
					}
				}
			}
		}
		
		printf("%d\n", dp[1][M][M]);
		
		vector<int> L1, L2;
		for(int i = 1, j = M, k = M; i<=N; i++) {
			if (A[i][j][k] == 1) {
				L1.push_back(i);
				j -= arr[i];
			}
			else if (A[i][j][k] == 2) {
				L2.push_back(i);
				k -= arr[i];
			}
		}
		
		printf("Lado A:");
		for(int i=0; i<(int)L1.size(); i++) {
			printf(" %d", L1[i]);
		}
		printf("\n");
		
		printf("Lado B:");
		for(int i=0; i<(int)L2.size(); i++) {
			printf(" %d", L2[i]);
		}
		printf("\n");
	}
}
