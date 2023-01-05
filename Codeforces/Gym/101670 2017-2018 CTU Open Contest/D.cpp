#include <bits/stdc++.h>
using namespace std;
#define MAXN 2000009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int n, x[MAXN], y[MAXN];
int nxtx[MAXN], nxty[MAXN];

int main() {
	while(scanf("%d", &n) != EOF) {
		map<int, vi > mx, my;
		map<ii, int> reduce;
		FOR1(i, n) {
			scanf("%d %d", &x[i], &y[i]);
			mx[x[i]].pb(y[i]);
			my[y[i]].pb(x[i]);
			reduce[{x[i], y[i]}] = i;
			nxtx[i] = -1;
			nxty[i] = -1;
		}
		for(auto &pp : mx) {
			int x = pp.fi;
			vi &vy = pp.se;
			sort(all(vy));
			FOR(i, sz(vy)-1) {
				int u = reduce[{x, vy[i]}];
				int v = reduce[{x, vy[i+1]}];
				nxty[u] = v;
			}
		}
		for(auto &pp : my) {
			int y = pp.fi;
			vi &vx = pp.se;
			sort(all(vx));
			FOR(i, sz(vx)-1) {
				int u = reduce[{vx[i], y}];
				int v = reduce[{vx[i+1], y}];
				nxtx[u] = v;
			}
		}
		int ans = 0;
		FOR1(w, n) {
			int u = w, v = w, dx, dy;
			while(u != -1 && v != -1) {
				dx = x[u]-x[w];
				dy = y[v]-y[w];
				if (dx == dy) {
					if (reduce.count({x[u], y[v]})) {
						ans = max(ans, x[u]-x[w]);
					}
					u = nxtx[u];
					v = nxty[v];
				}
				else if (dx > dy) v = nxty[v];
				else if (dx < dy) u = nxtx[u];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}