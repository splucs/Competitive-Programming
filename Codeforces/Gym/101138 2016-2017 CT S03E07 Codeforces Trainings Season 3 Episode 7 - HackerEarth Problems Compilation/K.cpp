#include <bits/stdc++.h>
using namespace std;
#define MAXN 3340
#define MOD 1000000007LL

typedef long long ll;
ll dp[MAXN][MAXN], col[MAXN][MAXN], diag[MAXN][MAXN];
int N, T, d;
ll k;

template<typename T>
T modExp(T a, T b, T m) {
    if (b == 0) return 1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c *= a;
    return c;
}

int main() {
	scanf("%d %d %d %I64d", &N, &d, &T, &k);
	for(int i=0; i<=N; i++) {
		for(int t=0; t<=T; t++) {
			if (i == 0) dp[i][t] = (t == 0 ? 1LL : 0LL);
			else if (t > i-d+1) dp[i][t] = 0;
			else if (t == 0) {
				if (i < d) dp[i][t] = modExp(k, (ll)i, MOD);
				else dp[i][t] = ((k-1)*D[t].rsq(i-d+1, i-1)) % MOD;
			}
			else {
				dp[i][t] = col[i-1][t] - col[i-d][t] + diag[i-d][t-1] - diag[0][d-1+t-i];
			}
			col[i][t] = dp[i][t] + (i > 0 ? col[i-1][t] : 0);
			diag[i][t] = dp[i][t] + (i > 0 && t > 0 ? diag[i-1][t-1] : 0);
			//printf("dp[%d][%d] = %I64d\n", i, t, dp[i][t]);
		}
	}
	/*if (d > 1)*/ //printf("%I64d\n", (dp[N][T]*modDiv(k, k-1, MOD)) % MOD);
	//else printf("%I64d\n", (T == N ? modExp(k, (ll)N, MOD) : 0));
	printf("%I64d\n", dp[N][T]);
	return 0;
}