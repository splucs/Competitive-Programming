#include <bits/stdc++.h>
using namespace std;
#define MAXN 42
#define MAXK 402
#define INF (1<<30)

int N, K, dp[MAXN][MAXN][MAXK][11], A[MAXN][MAXN][MAXK][11];
char arr[MAXN][MAXK];

void change(int i, int j, int k, int d) {
	if(j<i || k==K) return;
	for(int it=i; it<A[i][j][k][d]; it++) {
		arr[it][k] = d;
	}
	change(A[i][j][k][d], j, k, d+1);
	change(i, A[i][j][k][d]-1, k+1, 0);
}

int main() {
	scanf("%d %d", &N, &K);
	for(int i=0; i<N; i++) {
		scanf(" %s", arr[i]);
		for(int k=0; k<K; k++) {
			arr[i][k] -= '0';
		}
	}
	for(int k=K; k>=0; k--) {
		for(int d=10; d>=0; d--) {
			for(int i=0; i<N; i++) {
				for(int j=0; j<N; j++) {
					if(j<i || k==K) dp[i][j][k][d] = 0;
					else if (d==10) dp[i][j][k][d] = INF;
					else {
						dp[i][j][k][d] = INF;
						int cur = 0;
						for(int it=i; it<=j+1; it++) {
							int cost = cur + dp[it][j][k][d+1] + (it>i ? dp[i][it-1][k+1][0] : 0);
							if (dp[i][j][k][d] > cost) {
								dp[i][j][k][d] = cost;
								A[i][j][k][d] = it;
							}
							cur += (arr[it][k] == d ? 0 : 1);
						}
					}
				}
			}
		}
	}
	
	change(0, N-1, 0, 0);
	for(int i=0; i<N; i++) {
		for(int k=0; k<K; k++) {
			arr[i][k] += '0';
		}
		printf("%s\n", arr[i]);
	}
	return 0;
}
