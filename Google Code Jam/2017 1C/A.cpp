#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define r first
#define h second
#define EPS 1e-9
int T, N, K;

typedef pair<double, double> dd;
dd pc[MAXN];
double dp[MAXN][MAXN];

double DP(int i, int k) {
	if (dp[i][k] > -0.5) return dp[i][k];
	if (k == 0 || i == N) return dp[i][k] = 0.0;
	return dp[i][k] = max(2*M_PI*pc[i].r*pc[i].h + DP(i+1, k-1), DP(i+1, k));
}

bool comp(dd i, dd j) {
	if (fabs(i.r - j.r) < EPS) return i.h > j.h;
	return i.r > j.r;
}

int main(){
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++) {
		scanf("%d %d", &N, &K);
		for(int i=0; i<=N; i++) for(int j=0; j<=K; j++) dp[i][j] = -1.0;
		for(int i=0; i<N; i++) {
			scanf("%lf %lf", &pc[i].r, &pc[i].h);
		}
		sort(pc, pc+N, &comp);
		double ans = 0.0;
		for(int i=0; i<N; i++) {
			ans = max(ans, DP(i+1, K-1) + M_PI*pc[i].r*pc[i].r + 2*M_PI*pc[i].r*pc[i].h);
		}
		printf("Case #%d: %.9f\n", caseNo, ans);
	}
	return 0;
}