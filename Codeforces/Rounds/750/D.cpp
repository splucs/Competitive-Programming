#include <bits/stdc++.h>
using namespace std;
#define MAXN 39
#define MAXM 309
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
bool vis[MAXM][MAXM], dp[MAXM][MAXM][5][MAXN][8];
int n, t[MAXN];
#define state dp[i][j][l][k][d]

void DP(int i, int j, int l, int k, int d) {
	if (k == n) return;
	if (state) return;
	state = true;
	vis[i][j] = true;
	if (l > 0) {
		DP(i+dx[d], j+dy[d], l-1, k, d);
	}
	else {
		int d1 = (d+1)%8, d2 = (d+7)%8;
		DP(i+dx[d1], j+dy[d1], t[k+1]-1, k+1, d1);
		DP(i+dx[d2], j+dy[d2], t[k+1]-1, k+1, d2);
	}
}

int main() {
	memset(&vis, false, sizeof vis);
	FOR(i, MAXM) FOR(j, MAXM) FOR(l, 5) FOR(k, MAXN) FOR(d, 8) {
		state = false;
	}
	scanf("%d", &n);
	FOR(k, n) scanf("%d", &t[k]);
	DP(MAXM/2, MAXM/2, t[0]-1, 0, 0);
	int ans = 0;
	FOR(i, MAXM) FOR(j, MAXM) {
		if (vis[i][j]) ans++;
	}
	printf("%d\n", ans);
	return 0;
}