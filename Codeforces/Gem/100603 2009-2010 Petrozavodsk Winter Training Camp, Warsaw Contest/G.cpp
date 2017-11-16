#include <bits/stdc++.h>
using namespace std;
#define MAXN 609
#define MAXK 59

typedef long long ll;
ll dp[MAXN][MAXK], x[MAXN][MAXN], sum[MAXN][MAXN];
int A[MAXN][MAXK], N, K;

int main() {
	scanf("%d %d", &N, &K);
	memset(&x, 0, sizeof x);
	memset(&sum, 0, sizeof sum);
	for(int i=1; i<N; i++) {
		for(int j=i+1; j<=N; j++) {
			scanf("%I64d", &x[i][j]);
		}
	}
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			sum[i][j] = x[i][j] + sum[i-1][j] - sum[i-1][j-1] + sum[i][j-1];
		}
	}
	for(int i=1; i<=N; i++) {
		for(int k=0; k<=K; k++) {
			if (k == 0 || i == 1) dp[i][k] = 0;
			else {
				dp[i][k] = -1;
				for(int j=k; j<i; j++) {
					if (dp[i][k] < dp[j][k-1] + sum[j][i] - sum[j][j]) {
						dp[i][k] = dp[j][k-1] + sum[j][i] - sum[j][j];
						A[i][k] = j;
					}
				}
			}
		}
	}
	stack<int> ans;
	
	int i = N, k = K;
	while(k > 0) {
		ans.push(A[i][k]);
		i = A[i][k];
		k--;
	}
	while(!ans.empty()) {
		printf("%d ", ans.top());
		ans.pop();
	}
	printf("\n");
	return 0;
}