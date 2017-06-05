#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define state dp[i][j]

char S[MAXN], T[MAXN];
int n, m, dp[MAXN][MAXN], A[MAXN][MAXN];

int main() {
	scanf("%s %s", S, T);
	n = strlen(S);
	m = strlen(T);
	for(int i=0; i<n; i++) dp[i][m] = A[i][m] = 0;
	for(int j=0; j<m; j++) dp[n][j] = 0, A[n][j] = 1;
	dp[n][m] = 1;
	A[n][m] = 1;
	for(int i=n-1; i>=0; i--){
		for(int j=m-1; j>=0; j--){
			state = 0;
			if (S[i] == T[j]) {
				state = max(state, dp[i+1][j+1]);
				if (T[j] != T[j+1]) state = max(state, A[i+1][j+2]);
			}
			A[i][j] = max(dp[i][j], A[i][j+1]);
		}
	}
	if (dp[0][0]) printf("Yes\n");
	else printf("No\n");
	return 0;
}