#include <bits/stdc++.h>
using namespace std;
#define MAXN 17
#define INF (1<<30)

int x[MAXN], y[MAXN], N;
int dist[MAXN][MAXN], dp[1<<MAXN][MAXN];

int main() {
	int M;
	char c;
	while(scanf("%d", &M), M) {
		N = 1;
		for(int i=0; i<M; i++) {
			for(int j=0; j<M; j++) {
				scanf(" %c", &c);
				if (c == 'M') {
					x[N] = i;
					y[N] = j;
					N++;
				}
				if (c == 'D') {
					x[0] = i;
					y[0] = j;
				}
			}
		}
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				int dx = abs(x[i]-x[j]);
				int dy = abs(y[i]-y[j]);
				dist[i][j] = 2*(dx+dy) - min(dx, dy);
			}
		}
		for(int mask = (1<<N)-1; mask > 0; mask--) {
			for(int i=0; i<N; i++) {
				if (mask == (1<<N) - 1) dp[mask][i] = dist[i][0];
				else {
					dp[mask][i] = INF;
					for(int j=0; j<N; j++) {
						if (mask & (1<<j)) continue;
						dp[mask][i] = min(dp[mask][i], dp[mask | (1<<j)][j] + dist[i][j]);
					}
				}
			}
		}
		printf("%d\n", dp[1][0]);
	}
	return 0;
}