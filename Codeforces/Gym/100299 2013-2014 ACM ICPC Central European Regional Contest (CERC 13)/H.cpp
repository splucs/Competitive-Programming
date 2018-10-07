#include <bits/stdc++.h>
using namespace std;
#define MAXN 4009
#define MAXLOGN 20
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int n;

bool solve(vi &xb, vi &xt, vi &yb, vi &yt, vi &zb, vi &zt) {
	int zmin = INF, zmax = -INF;
	int xbmin = INF, xbmax = -INF;
	int xtmin = INF, xtmax = -INF;
	int ybmin = INF, ybmax = -INF;
	int ytmin = INF, ytmax = -INF;
	int cnt = 0;
	FOR(i, n) {
		if (zb[i] != zt[i]) continue;
		cnt++;
		xbmin = min(xbmin, xb[i]); xbmax = max(xbmax, xb[i]);
		xtmin = min(xtmin, xt[i]); xtmax = max(xtmax, xt[i]);
		ybmin = min(ybmin, yb[i]); ybmax = max(ybmax, yb[i]);
		ytmin = min(ytmin, yt[i]); ytmax = max(ytmax, yt[i]);
		zmin = min(zmin, zb[i]); zmax = max(zmax, zb[i]);
	}
	if (cnt == 0 || cnt == n) return false;
	if (xtmin <= xbmax) return false;
	if (ytmin <= ybmax) return false;
	FOR(i, n) {
		if (zb[i] == zt[i]) continue;
		if (zt[i] <= zmax || zb[i] >= zmin) return false;
		if (xb[i] == xt[i]) {
			int x = xb[i];
			if (x <= xbmax || x >= xtmin) return false;
			bool ok = false;
			if (yt[i] > ybmax && yb[i] < ybmin) ok = true;
			if (yt[i] > ytmax && yb[i] < ytmin) ok = true;
			if (!ok) return false;
		}
		if (yb[i] == yt[i]) {
			int y = yb[i];
			if (y <= ybmax || y >= ytmin) return false;
			bool ok = false;
			if (xt[i] > xbmax && xb[i] < xbmin) ok = true;
			if (xt[i] > xtmax && xb[i] < xtmin) ok = true;
			if (!ok) return false;
		}
	}
	return true;
}

int main() {
	vi xb, xt, yb, yt, zb, zt;
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d", &n);
		xb.resize(n); xt.resize(n);
		yb.resize(n); yt.resize(n);
		zb.resize(n); zt.resize(n);
		FOR(i, n) {
			scanf("%d %d %d", &xb[i], &yb[i], &zb[i]);
			scanf("%d %d %d", &xt[i], &yt[i], &zt[i]);
			if (xb[i] > xt[i]) swap(xb[i], xt[i]);
			if (yb[i] > yt[i]) swap(yb[i], yt[i]);
			if (zb[i] > zt[i]) swap(zb[i], zt[i]);
		}
		bool ok = false;
		ok = ok || solve(xb, xt, yb, yt, zb, zt);
		ok = ok || solve(zb, zt, xb, xt, yb, yt);
		ok = ok || solve(yb, yt, zb, zt, xb, xt);
		if (ok) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}