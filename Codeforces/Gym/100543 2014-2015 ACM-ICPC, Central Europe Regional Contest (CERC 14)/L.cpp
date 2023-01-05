#include <bits/stdc++.h>
using namespace std;
#define MAXN 609
#define MAXM 1000009
#define INF 0x3f3f3f3f
#define MOD 1000000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mset(x, y) memset(&x, y, sizeof x)
#define sz(x) int(x.size())
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

int st[MAXN], en[MAXN], d[MAXN];
int dp[MAXN][MAXN];

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int n;
		scanf("%d", &n);
		map<int, int> reduce;
		FOR1(i, n) {
			scanf("%d %d %d", &st[i], &en[i], &d[i]);
			reduce[st[i]] = 0;
			reduce[en[i]] = 0;
		}
		int cnt = 0;
		for(auto &pp : reduce) pp.se = ++cnt;
		FOR1(i, n) {
			st[i] = reduce[st[i]];
			en[i] = reduce[en[i]];
		}
		FOR1(s, cnt+1) FOR(i, cnt+1) {
			int j = i+s;
			if (j > cnt+1) break;
			int mx = 0;
			FOR1(it, n) {
				if (st[it] <= i || en[it] >= j) continue;
				mx = max(mx, d[it]);
			}
			if (mx == 0) {
				dp[i][j] = 0;
				continue;	
			}
			dp[i][j] = INF;
			for(int k = i+1; k < j; k++) {
				dp[i][j] = min(dp[i][j], mx + dp[i][k] + dp[k][j]);
			}
		}
		printf("%d\n", dp[0][cnt+1]);
	}
	return 0;
}