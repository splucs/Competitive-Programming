#include <bits/stdc++.h>
using namespace std;
#define MAXN 309

int N, M, dp[MAXN][MAXN][MAXN], arr[MAXN];
int last[MAXN], ans[MAXN];

int main() {
	scanf("%d %d", &N, &M);
	for(int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	for(int s = 0; s < N; s++) {
		for(int i = 0; i+s < N; i++) {
			int j = i+s;
			if (i == j) {
				for(int c = 1; c <= M; c++) dp[i][j][c] = 0;
			}
			else {
				for(int c = 1; c <= M; c++) {
					last[c] = i-1;
					ans[c] = 0;
				}
				for(int k = i; k <= j; k++) {
					int c = arr[k];
					ans[c] += 1 + (last[c]+1 <= k-1 ? dp[last[c]+1][k-1] : 0);
					ans[c] = min(ans[c], )
					last[c] = k;
				}
			}
		}
	}
}