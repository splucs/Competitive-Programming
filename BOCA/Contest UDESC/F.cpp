#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF (1<<30)
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;

int N, L, R;
map<int, vector<ii> > lines;
vector<pair<int, double> > f;

int xt[MAXN], xb[MAXN], yt[MAXN], yb[MAXN];

ii get(int s, int j) {
	int l = max((s-xt[j]) - xt[j], yb[j] - (s-yb[j]));
	int r = min((s-xb[j]) - xb[j], yt[j] - (s-yt[j]));
	return ii(l, r);
}

int main() {
	scanf("%d %d %d", &N, &L, &R);
	FOR(i, N) {
		scanf("%d %d %d %d", &xb[i], &yb[i], &xt[i], &yt[i]);
	}
	FOR(i, N) FOR(j, N) {
		int s;
		s = xb[i]+yb[i];
		lines[s].pb(get(s, j));
		s = xb[i]+yt[i];
		lines[s].pb(get(s, j));
		s = xt[i]+yb[i];
		lines[s].pb(get(s, j));
		s = xt[i]+yt[i];
		lines[s].pb(get(s, j));
	}
	for(auto & pp : lines) {
		vector<ii> & v = pp.second;
		sort(all(v));
		int last = -INF;
		double cur = 0;
		for(ii pr : v) {
			//printf("pair %d-%d\n", pr.first, pr.second);
			pr.first = max(pr.first, last);
			last = max(last, pr.second);
			if (pr.second >= pr.first)
				cur += pr.second - pr.first;
		}
		cur /= 2;
		f.pb({pp.first, cur});
		//printf("f(%d) = %.3f\n", pp.first, cur);
	}
	double ans = 0;
	FOR(i, int(f.size())) {
		if (i == 0) continue;
		int ds = f[i].first - f[i-1].first;
		double df = f[i].second - f[i-1].second;
		
		//printf("block %d-%d\n", f[i-1].first, f[i].first);
		int l = max(L, f[i-1].first);
		int dx = l - f[i-1].first;
		double dy = df*dx*1.0/ds;
		double fl = f[i-1].second + dy;
		
		int r = min(R, f[i].first);
		dx = r - f[i-1].first;
		dy = df*dx*1.0/ds;
		double fr = f[i-1].second + dy;
		//printf("f(%d) = %.3f f(%d) = %.3f\n", l, fl, r, fr);
		if (i >= 1 && f[i-1].first >= L && f[i-1].first <= R) ans -= fl;
		
		if(r >= l) ans += (fl+fr)*(r-l+1)/2.0;
	}
	printf("%d\n", int(ans + 0.5));
	return 0;
}
