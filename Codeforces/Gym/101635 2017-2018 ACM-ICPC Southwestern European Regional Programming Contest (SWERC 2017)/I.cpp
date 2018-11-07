#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define MAXM 5009
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define PI (acos(-1.0))
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) ((int)x.size())
typedef long long ll;
typedef pair<int,int> ii;

int dp[MAXN][10][10];
int nxt[MAXN][MAXM], prv[MAXN][MAXM], psum[MAXN][MAXM];
int n, m;
vector<int> ladders[MAXN];
char field[MAXN][MAXM];

int main() {
	scanf("%d %d", &n, &m);
	FOR(it, n) {
		int i = 2*it;
		scanf(" %s %s", field[i], field[i+1]);
		int last = 0, acum = 0;
		FOR(j, m) {
			if ('0' <= field[i][j] && field[i][j] <= '9') {
				acum += field[i][j] - '0';
				last = j;
			}
			psum[i][j] = acum;
			prv[i][j] = last;
		}
		last = m-1;
		REP(j, m) {
			if ('0' <= field[i][j] && field[i][j] <= '9') last = j;
			nxt[i][j] = last;
		}
		FOR(j, m) {
			if (field[i+1][j] == '|') ladders[i+1].pb(j);
		}
	}
	n *= 2;

	for(int i = n; i > 0; i -= 2) {
		FOR(rt, sz(ladders[i-1])) FOR(lt, rt) {
			int l = ladders[i-1][lt];
			int r = ladders[i-1][rt];

			int l0 = prv[i][l];
			int r0 = nxt[i][r];
			dp[i][lt][rt] = 0;
			dp[i][lt][rt] += psum[i][r0];
			if (l0 > 0) dp[i][lt][rt] -= psum[i][l0-1];

			FOR(qt, sz(ladders[i+1])) FOR(pt, qt) {
				int p = ladders[i+1][pt];
				int q = ladders[i+1][qt];
				if (p >= r || q <= l) continue;

				int s1 = prv[i][min(p, l)];
				int s2 = nxt[i][max(p, l)];
				int s3 = prv[i][min(q, r)];
				int s4 = nxt[i][max(q, r)];
				if (s2 >= s3) s2 = s3-1;

				int cur = dp[i+2][pt][qt];
				if (s2 >= s1) cur += psum[i][s2] - (s1 > 0 ? psum[i][s1-1] : 0);
				if (s4 >= s3) cur += psum[i][s4] - (s3 > 0 ? psum[i][s3-1] : 0);
				dp[i][lt][rt] = max(dp[i][lt][rt], cur);
			}
		}
	}

	int ans = 0;
	FOR(rt, sz(ladders[1])) FOR(lt, rt) {
		ans = max(ans, dp[2][lt][rt]);
	}

	printf("%d\n", ans);
	return 0;
}