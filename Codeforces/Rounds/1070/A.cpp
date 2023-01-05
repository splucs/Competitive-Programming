#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define MAXM 509
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> ii;

int prvi[MAXN][MAXM], prvj[MAXN][MAXM], prvk[MAXN][MAXM];
int dist[MAXN][MAXM], s, d;
int qs[MAXN*MAXM], qd[MAXN*MAXM], en = 0;
int ans[MAXN];

int main() {
	scanf("%d %d", &d, &s);
	FOR1(i, 9) {
		int j = i%d;
		qs[en] = i;
		qd[en] = j;
		prvi[i][j] = -1;
		prvj[i][j] = -1;
		prvk[i][j] = i;
		dist[i][j] = 1;
		en++;
	}
	FOR(st, en) {
		int i = qs[st];
		int j = qd[st];
		if (i == s && j == 0) break;
		FOR(k, 10) {
			int ni = i + k;
			int nj = (j*10 + k)%d;
			if (ni > s || dist[ni][nj]) continue;
			dist[ni][nj] = 1 + dist[i][j];
			prvi[ni][nj] = i;
			prvj[ni][nj] = j;
			prvk[ni][nj] = k;
			qs[en] = ni;
			qd[en] = nj;
			en++;
		}
	}
	if (dist[s][0] == 0) printf("-1\n");
	else {
		int i = s, j = 0;
		int sz = 0;
		while(i != -1) {
			ans[sz++] = prvk[i][j];
			int ti = prvi[i][j];
			int tj = prvj[i][j];
			i = ti, j = tj;
		}
		reverse(ans, ans+sz);
		FOR(i, sz) printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}