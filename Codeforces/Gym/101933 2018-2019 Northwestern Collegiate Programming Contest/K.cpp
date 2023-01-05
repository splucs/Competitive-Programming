#include <bits/stdc++.h>
using namespace std;
#define MAXN 2509
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;

int pascal[MAXN][MAXN];

int modExp(int a, int b) {
	if (b == 0) return 1;
	int c = modExp(a, b/2);
	c = (c*1ll*c) % MOD;
	if (b % 2 != 0) c = (a*1ll*c) % MOD;
	return c;
}

int solve(int n, int k) {
	return (k*1ll*modExp(k-1, n-1)) % MOD;
}

int main() {
	FOR(i, MAXN) FOR(j, MAXN) {
		if (j > i) pascal[i][j] = 0;
		else if (j == 0 || i == j) pascal[i][j] = 1;
		else pascal[i][j] = (pascal[i-1][j] + pascal[i-1][j-1]) % MOD;
	}

	int n, k;
	scanf("%d %d", &n, &k);
	int ans = 0;
	REP1(i, k) {
		int cur = (pascal[k][i]*1ll*solve(n, i)) % MOD;
		if ((k-i) %2 == 0) ans = (ans + cur) % MOD;
		else ans = (ans - cur + MOD) % MOD;
	}
	printf("%d\n", ans);

	return 0;
}