#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 1009
#define INF (1 << 30)

int dp[MAXN][MAXN], C[MAXN][MAXN], N, K;

void calculatedp(int min_i, int max_i, int j, int min_k, int max_k) {
	if (min_i > max_i) return;
	int i = (min_i + max_i)/2;
	int ans = INF, opt;
	for(int k=min_k; k<=min(max_k, i-1); k++) {
		if (ans > dp[k][j-1] + C[k][i]) {
			opt = k;
			ans = dp[k][j-1] + C[k][i];
		}
	}
	dp[i][j] = ans;
	calculatedp(min_i, i-1, j, min_k, opt);
	calculatedp(i+1, max_i, j, opt, max_k);
}

void solve() {
	for(int i=0; i<=N; i++) dp[i][0] = 0;
	for(int j=0; j<=K; j++) dp[0][j] = 0;
	for(int j=1; j<=K; j++) {
		calculatedp(1, N, j, 0, N-1);
	}
}

int main() {

}