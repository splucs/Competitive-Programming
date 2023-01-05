#include <cstdio>
#define MAXN 1009
#define INF (1LL << 60)

typedef long long ll;

ll dp[MAXN][MAXN], C[MAXN][MAXN], M, x[MAXN];
int A[MAXN][MAXN], N, S;

void knuth() {
	ll cur;
	for(int s = 0; s < N; s++) {
		for(int i=0, j; i + s<N; i++) {
			j = i + s;
			if (s < S) {	//Condições iniciais
				dp[i][j] = 0;
				A[i][j] = i;
				continue;
			}
			dp[i][j] = INF;
			for(int k = A[i][j-1]; k <= A[i+1][j]; k++) {
				cur = C[i][j] + dp[i][k] + dp[k][j];
				if (dp[i][j] > cur) {
					dp[i][j] = cur;
					A[i][j] = k;
				}
			}
		}
	}
}

int main() {
	while(scanf("%lld %d", &M, &N)!=EOF) {
		for(int i=1; i<=N; i++) {
			scanf("%lld", &x[i]);
		}
		x[0] = 0;
		x[N+1] = M;
		N += 2;
		S = 2;
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				C[i][j] = x[j] - x[i];
			}
		}
		knuth();
		printf("%lld\n", dp[0][N-1]);
	}
	return 0;
}