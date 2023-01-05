#include <bits/stdc++.h>
#define MAXN 1000009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;

int n, m, a[MAXN];

int main() {
	scanf("%d %d", &n, &m);
	FOR(i, m) {
		int x;
		scanf("%d", &x);
		a[x]++;
	}
	map<int, int> dp;
	dp[0] = 1;
	int off = 0;
	REP1(i, n) {
		off += a[i]-1;
		if (a[i] == 0) dp[off] = (dp[off] + dp[off+1]) % MOD;
	}
	printf("%d\n", dp[off]);
	return 0;
}