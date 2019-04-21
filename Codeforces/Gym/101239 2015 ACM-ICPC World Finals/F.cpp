#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define MAXN 10009
#define MAXM 59
#define INF 0x3f3f3f3f
typedef long long ll;
typedef pair<int, int> ii;

int n, m, len;
char str[MAXN], key[MAXM][MAXM];

bool valid(int i, int j) {
	return i >= 0 && i < n && j >= 0 && j < m;
}

int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

int nxti[MAXM][MAXM][4];
int nxtj[MAXM][MAXM][4];

void getdest(int &i, int &j, int k) {
	int oi = i, oj = j;
	char c = key[i][j];
	while (valid(i, j) && key[i][j] == c) {
		i += di[k];
		j += dj[k];
	}
	if (!valid(i, j)) {
		i = oi;
		j = oj;
	}
}

void computeNxt() {
	FOR(i, n) FOR(j, m) FOR(k, 4) {
		nxti[i][j][k] = i;
		nxtj[i][j][k] = j;
		getdest(nxti[i][j][k], nxtj[i][j][k], k);
	}
}

int dist[MAXM][MAXM][MAXN];
int qi[MAXN*MAXM*MAXM];
int qj[MAXN*MAXM*MAXM];
int ql[MAXN*MAXM*MAXM];

int bfs() {
	FOR(i, n) FOR(j, m) FOR(l, len+1) {
		dist[i][j][l] = INF;
	}
	int en = 0;
	qi[en] = qj[en] = ql[en] = 0;
	dist[0][0][0] = 0;
	en++;
	FOR(st, en) {
		int i = qi[st];
		int j = qj[st];
		int l = ql[st];
		FOR(k, 4) {
			int ni = nxti[i][j][k], nj = nxtj[i][j][k];
			if (dist[ni][nj][l] == INF) {
				dist[ni][nj][l] = 1 + dist[i][j][l];
				qi[en] = ni;
				qj[en] = nj;
				ql[en] = l;
				en++;
			}
		}
		if (l < len && key[i][j] == str[l]) {
			if (dist[i][j][l+1] == INF) {
				dist[i][j][l+1] = 1 + dist[i][j][l];
				qi[en] = i;
				qj[en] = j;
				ql[en] = l+1;
				en++;
			}
		}
	}
	int ans = INF;
	FOR(i, n) FOR(j, m) {
		if (key[i][j] == '*') ans = min(ans, 1+dist[i][j][len]);
	}
	return ans;
}

int main() {
	scanf("%d %d", &n, &m);
	FOR(i, n) scanf(" %s", key[i]);
	scanf(" %s", str);
	len = strlen(str);
	computeNxt();
	printf("%d\n", bfs());
	return 0;
}