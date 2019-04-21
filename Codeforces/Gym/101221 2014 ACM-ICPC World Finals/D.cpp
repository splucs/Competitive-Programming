#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(inr i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(inr i = n-; i > 0; i--)
#define fi first
#define se second
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;
typedef long double ld;
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define MAXN 50
#define MAXM 1000059

int read() {
	char buffer[30];
	scanf(" %s", buffer);
	int m = strlen(buffer);
	int mask = 0;
	FOR(i, m) {
		mask |= (1<<(buffer[i]-'a'));
	}
	return mask;
}

vector<int> g[MAXM], rev[MAXM];
int cnt = 0, d[MAXN][MAXM], n;
int type[MAXM];

map<int, int> red;
int reduce(int mask) {
	if (!red.count(mask)) {
		type[cnt] = 2;
		FOR(i, n) {
			if (mask & (1<<i)) {
				g[cnt].pb(i);
				rev[i].pb(cnt);
			}
		}
		red[mask] = cnt++;
	}
	return red[mask];
}

bitset<MAXM> change[MAXN];
int ans[MAXN][MAXN];

void solve(int t) {
	FOR(h, MAXN) {
		change[h].reset();
		FOR(u, cnt) d[h][u] = INF;
	}
	d[0][t] = 0;
	for (int v : rev[t]) {
		change[1][v] = 1;
	}
	FOR1(h, MAXN-1) {
		FOR(u, cnt) {
			if (!change[h][u]) {
				d[h][u] = d[h-1][u];
				continue;
			}
			int val = (type[u] == 2 ? 0 : INF);
			for(int v : g[u]) {
				if (type[u] == 2) val = max(val, 1+d[h-1][v]);
				if (type[u] == 1) val = min(val, 1+d[h-1][v]);
			}
			if (u == t) val = 0;
			d[h][u] = val;
			if (d[h][u] == d[h-1][u] || h+1 == MAXN) continue;
			for (int v : rev[u]) {
				change[h+1][v] = 1;
			}
		}
	}
	FOR(i, n) ans[i][t] = d[MAXN-1][i]/2;
}

int main() {
	scanf("%d", &n);
	FOR(i, n) type[cnt++] = 1;
	FOR(i, n) {
		int k;
		scanf("%d", &k);
		while(k --> 0) {
			int mask = read();
			if (mask & (1<<i)) continue;
			g[i].pb(reduce(mask));
			rev[reduce(mask)].pb(i);
		}
	}
	FOR(t, n) solve(t);
	FOR(i, n) {
		FOR(j, n) printf("%d ", ans[i][j] > 60 ? -1 : ans[i][j]);
		printf("\n");
	}
	return 0; 
}