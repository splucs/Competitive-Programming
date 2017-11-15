#include <bits/stdc++.h>
using namespace std;
#define MAXN 51

double dp[MAXN][MAXN][MAXN][MAXN][2];
int dom[MAXN], cnt;

int main() {
	int N, K;
	while(scanf("%d %d", &N, &K) != EOF) {
		cnt = 0;
		for(int i=1; i<=N; i++) {
			int v;
			scanf("%d", &v);
			while(v --> 0) {
				dom[++cnt] = i;
			}
		}
		
		int h[6];
		double ans[6];
		for(int j=1; j<=5; j++) ans[j] = 0;
		for(int i=0; i<=K; i++) {
			for(h[1]=0; h[1]<=i; h[1]++) {
				for(h[2]=0; h[1]+h[2]<=i; h[2]++) {
					for(h[3]=0; h[1]+h[2]+h[3]<=i; h[3]++) {
						for(h[4]=0; h[1]+h[2]+h[3]+h[4]<=i; h[4]++) {
							h[5] = i-h[1]-h[2]-h[3]-h[4];
							if (i == 0) {
								dp[h[1]][h[2]][h[3]][h[4]][i%2] = 1.0;
							}
							else {
								double prob[6];
								if (i <= cnt) {
									for(int j=1; j<=5; j++) prob[j] = 0;
									prob[dom[i]] = 1.0;
								}
								else {
									for(int j=1; j<=5; j++) {
										if (h[j] > 0) prob[j] = (h[j]-1.0)/(i-1.0);
									}
								}
								dp[h[1]][h[2]][h[3]][h[4]][i%2] = 0;
								if(h[1] > 0) dp[h[1]][h[2]][h[3]][h[4]][i%2] += prob[1]*dp[h[1]-1][h[2]][h[3]][h[4]][(i+1)%2];
								if(h[2] > 0) dp[h[1]][h[2]][h[3]][h[4]][i%2] += prob[2]*dp[h[1]][h[2]-1][h[3]][h[4]][(i+1)%2];
								if(h[3] > 0) dp[h[1]][h[2]][h[3]][h[4]][i%2] += prob[3]*dp[h[1]][h[2]][h[3]-1][h[4]][(i+1)%2];
								if(h[4] > 0) dp[h[1]][h[2]][h[3]][h[4]][i%2] += prob[4]*dp[h[1]][h[2]][h[3]][h[4]-1][(i+1)%2];
								if(h[5] > 0) dp[h[1]][h[2]][h[3]][h[4]][i%2] += prob[5]*dp[h[1]][h[2]][h[3]][h[4]][(i+1)%2];
							}
							if (i == K) {
								int mx = 0;
								for(int j=1; j<=5; j++) mx = max(mx, h[j]);
								int cntmx = 0;
								for(int j=1; j<=5; j++) if (h[j] == mx) cntmx++;
								for(int j=1; j<=5; j++) if (h[j] == mx) ans[j] += dp[h[1]][h[2]][h[3]][h[4]][i%2]/cntmx;
							}
						}
					}
				}
			}
		}
		
		for(int j=1; j<=N; j++) {
			printf("pub %d: %.2f %%\n", j, ans[j]*100.0);
		}
	}
	
	return 0;
}