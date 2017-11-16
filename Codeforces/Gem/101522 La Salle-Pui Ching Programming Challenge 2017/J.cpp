#include <bits/stdc++.h>
using namespace std;
#define MAXN 201
#define INF (1LL<<60)

typedef long long ll;
ll dp[MAXN][MAXN][MAXN][3];
char ans[3*MAXN];

int main() {
	for(int k=0; k<MAXN; k++) {
		for(int j=0; j<MAXN; j++) {
			for(int i=0; i<MAXN; i++) {
				for(int c=0; c<3; c++) {
					if (i+j+k == 0) {
						dp[i][j][k][c] = 1;
						continue;
					}
					
					dp[i][j][k][c] = 0;
					if (c == 0) {
						if (j > 0) dp[i][j][k][c] += dp[i][j-1][k][1];
						if (k > 0) dp[i][j][k][c] += dp[i][j][k-1][2];
					}
					if (c == 1) {
						if (i > 0) dp[i][j][k][c] += dp[i-1][j][k][0];
						if (k > 0) dp[i][j][k][c] += dp[i][j][k-1][2];
					}
					if (c == 2) {
						if (i > 0) dp[i][j][k][c] += dp[i-1][j][k][0];
						if (j > 0) dp[i][j][k][c] += dp[i][j-1][k][1];
					}
					if (dp[i][j][k][c] > INF) dp[i][j][k][c] = INF;
					
				}
			}
		}
	}
	
	int B, R, S;
	ll K;
	
	scanf("%d %d %d %I64d", &B, &R, &S, &K);
	bool ok = true;
	int last = 3, k = 0;
	while(B > 0 || R > 0 || S > 0) {
		if (B > 0 && last != 0) {
			//printf("dp[%d][%d][%d][%d] = %I64d\n", B-1, R, S, 0, dp[B-1][R][S][0]);
			if (dp[B-1][R][S][0] >= K) {
				B--;
				last = 0;
				ans[k++] = 'B';
				continue;
			}
			else K -= dp[B-1][R][S][0];
		}
		if (R > 0 && last != 1) {
			//printf("dp[%d][%d][%d][%d] = %I64d\n", B, R-1, S, 1, dp[B][R-1][S][1]);
			if (dp[B][R-1][S][1] >= K) {
				R--;
				last = 1;
				ans[k++] = 'R';
				continue;
			}
			else K -= dp[B][R-1][S][1];
		}
		if (S > 0 && last != 2) {
			//printf("dp[%d][%d][%d][%d] = %I64d\n", B, R, S-1, 2, dp[B][R][S-1][2]);
			if (dp[B][R][S-1][2] >= K) {
				S--;
				last = 2;
				ans[k++] = 'S';
				continue;
			}
			else K -= dp[B][R][S-1][2];
		}
		ok = false;
		break;
	}
	ans[k] = 0;
	
	if (ok) printf("%s\n", ans);
	else printf("None\n");
	
	return 0;
}