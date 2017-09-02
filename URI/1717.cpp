#include <bits/stdc++.h>
using namespace std;
#define MAXN 409
#define INF 1e+18

int N;
double dp[MAXN][MAXN], x[MAXN], y[MAXN], dist[MAXN][MAXN];

inline int type(int i, int j) {
	if ((j-i)%2 == 0) return 2;
	else return 1;
}

int main() {
	scanf("%d", &N);
	N <<= 1;
	for(int i=0; i<N; i++) {
		scanf("%lf %lf", &x[i], &y[i]);
		x[i+N] = x[i];
		y[i+N] = y[i];
	}
	for(int i=0; i<2*N; i++) {
		for(int j=0; j<2*N; j++) {
			if (abs(i-j) == 1) dist[i][j] = 0;
			else dist[i][j] = hypot(x[i] - x[j], y[i] - y[j]);
		}
	}
	for(int s=0; s<2*N; s++) {
		for(int i=0, j; i+s<2*N; i++) {
			j = i+s;
			if (s <= 3) dp[i][j] = 0;
			else if (type(i, j) == 2) {
				dp[i][j] = INF;
				for(int k=i+1; k<j; k+=2) {
					dp[i][j] = min(dp[i][j], dist[i][k] + dist[k][j] + dp[i][k] + dp[k][j]);
				}
			}
			else if (type(i, j) == 1) {
				dp[i][j] = dist[i+1][j-1] + dp[i+1][j-1];
				for(int k=i+1; k<j; k+=2) {
					dp[i][j] = min(dp[i][j], dist[i][k] + dp[i][k] + dp[k][j]);
				}
				for(int k=i+2; k<j; k+=2) {
					dp[i][j] = min(dp[i][j], dist[k][j] + dp[i][k] + dp[k][j]);
				}
			}
		}
	}
	double ans = INF;
	for(int i=0; i<N; i++) {
		for(int j=i+1; j<N; j++) {
			if (type(i, j) == 2) continue;
			ans = min(ans, dp[i][j] + dp[j][i+N] + dist[i][j]);
		}
	}
	printf("%.4f\n", ans);
	return 0;
}