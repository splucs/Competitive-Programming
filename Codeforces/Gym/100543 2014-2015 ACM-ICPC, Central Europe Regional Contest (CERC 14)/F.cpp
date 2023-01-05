#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define INF 0x3f3f3f3f
#define MOD 1000000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef vector<int> vi;

int cnt[3][3][28][28][28], dp[MAXN][3][3];
char s[3][MAXN];
int sz[3];

int main() {
	FOR1(i, 27) FOR1(j, 27) FOR1(k, 27) {
		int b1 = 0, b2 = 0;
		if (i == j) b1 = 1;
		if (i < j) b1 = 2;
		if (j == k) b2 = 1;
		if (j < k) b2 = 2;
		cnt[b1][b2][i][j][k]++;
		if (i > 1) cnt[b1][b2][0][j][k]++;
		if (j > 1) cnt[b1][b2][i][0][k]++;
		if (i > 1 && j > 1) cnt[b1][b2][0][0][k]++;
		if (k > 1) cnt[b1][b2][i][j][0]++;
		if (k > 1 && i > 1) cnt[b1][b2][0][j][0]++;
		if (k > 1 && j > 1) cnt[b1][b2][i][0][0]++;
		if (k > 1 && i > 1 && j > 1) cnt[b1][b2][0][0][0]++;
	}
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int n = 0;
		scanf(" %s %s %s", s[0], s[1], s[2]);
		FOR(j, 3) n = max(n, sz[j] = strlen(s[j]));
		FOR(j, 3) {
			while(sz[j] < n) s[j][sz[j]++] = 'a'-1;
			FOR(i, n) {
				if (s[j][i] == '?') s[j][i] = 0;
				else s[j][i] -= 'a'-2;
				//printf("%2d ", s[j][i]);
			}
			//printf("\n");
		}
		REP(i, n+1) FOR(a1, 3) FOR(a2, 3) {
			if (i == n) {
				if (a1 == 2 && a2 == 2) dp[i][a1][a2] = 1;
				else dp[i][a1][a2] = 0;
			}
			else if (a1 == 0 || a2 == 0) {
				dp[i][a1][a2] = 0;
			}
			else {
				dp[i][a1][a2] = 0;
				FOR(b1, 3) FOR(b2, 3) {
					int c1 = (a1 == 2 ? 2 : b1);
					int c2 = (a2 == 2 ? 2 : b2);
					dp[i][a1][a2] = (
						dp[i][a1][a2] + 
						cnt[b1][b2][s[0][i]][s[1][i]][s[2][i]]*1ll*
						dp[i+1][c1][c2]
					) % MOD;
				}
			}
		}
		printf("%d\n", dp[0][1][1]);
	}
	return 0;
}