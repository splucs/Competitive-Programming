#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define MAXN 609
#define MAXM 29
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;

int a[MAXN];
int dp[MAXN][64];
char s[MAXN];

int getshift() {
	scanf(" %s", s);
	int mx = -1;
	int ans = -1;
	FOR(i, 7) {
		int cur = 0;
		FOR(j, 7) {
			cur = (cur*10 + s[(i+j)%7] - '0');
		}
		if (cur > mx) {
			mx = cur;
			ans = i;
		}
	}
	bool alleq = true;
	FOR1(i, 6) if (s[i] != s[0]) alleq = false;
	if (alleq) ans = -1;
	return ans;
}

int sum[64];

int main() {
	FOR(mask, (1<<6)) {
		sum[mask] = 0;
		FOR(j, 6) {
			if (mask & (1<<j)) sum[mask] += j+1;
		}
		sum[mask] %= 7;
	}

	int n;
	while(scanf("%d", &n) != EOF) {
		int sz = 0;
		FOR(i, n) {
			int sft = getshift();
			if (sft != -1) a[++sz] = sft;
		}
		FOR(i, sz+1) FOR(mask, (1<<6)) {
			if (i == 0) {
				dp[i][mask] = 0;
				continue;
			}
			dp[i][mask] = INF;
			int ns, extra, inter;
			FOR(sub, (1<<6)) {
				if (sum[sub] != a[i]) continue;
				inter = sub&mask;
				extra = sub^inter;
				ns = __builtin_popcount(extra);
				if (dp[i][mask] > ns + dp[i-1][sub])
					dp[i][mask] = ns + dp[i-1][sub];
			}
		}
		printf("%d\n", dp[sz][0]);
	}
	return 0;
}