#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define MOD 1000000007
typedef long long ll;
typedef pair<ll, ll> ii;

int on(int mask, int i) {
	mask |= (1<<i);
	return mask;
}

bool ison(int mask, int i) {
	return on(mask, i) == mask;
}

int off(int mask, int i) {
	if (mask & (1<<i)) mask ^= (1<<i);
	return mask;
}

bool isoff(int mask, int i) {
	return off(mask, i) == mask;
}

int dp0[22][22][1<<20];
int solve0(int n, int m) {
	REP(i, n+1) REP(j, m+1) FOR(mask, (1<<m)) {
		if (i == n) dp0[i][j][mask] = (mask == 0 ? 1 : 0);
		else if (j == m) dp0[i][j][mask] = dp0[i+1][0][mask];
		else {
			dp0[i][j][mask] = dp0[i][j+1][off(mask, j)];
			if (j+1 < m && isoff(mask, j) && isoff(mask, j+1)) {
				dp0[i][j][mask] += dp0[i][j+2][on(on(mask, j), j+1)];
				dp0[i][j][mask] %= MOD;
			}
		}
	}
	return dp0[0][0][0];
}

int main() {
	printf("%d\n", solve0(1, 1));
	printf("%d\n", solve0(2, 2));
	printf("%d\n", solve0(3, 3));
	printf("%d\n", solve0(4, 4));
}