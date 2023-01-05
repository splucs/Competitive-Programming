#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define MAXN 500009
#define MAXM 59
#define INF 0x3f3f3f3f
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<double, double> dd;

vector<dd> unite(vector<dd> arr) {
	sort(all(arr));
	vector<dd> ans;
	for(dd p : arr) {
		if (!ans.empty() && ans.back().se >= p.fi) {
			ans.back().se = max(ans.back().se, p.se);
		}
		else ans.pb(p);
	}
	return ans;
}

int main() {
	int n;
	double w, u, v, t1, t2;
	scanf("%d %lf %lf %lf %lf %lf", &n, &w, &u, &v, &t1, &t2);
	vector<dd> forbidden;
	forbidden.pb({-(1e+30), t1});
	forbidden.pb({t2, 1e+30});
	FOR(i, n) {
		char c;
		int m;
		scanf(" %c %d", &c, &m);
		while(m --> 0) {
			double l, x1, x2;
			scanf("%lf %lf", &l, &x1);
			if (c == 'E') x1 *= -1;
			x2 = x1 + l;
			x1 -= w*u/v;
			double dx = u*i*w/v;
			x1 -= dx, x2 -= dx;
			t1 = x1/u;
			t2 = x2/u;
			forbidden.pb({t1, t2});
		}
	}
	forbidden = unite(forbidden);
	double ans = 0;
	FOR(i, sz(forbidden)-1) {
		ans = max(ans, forbidden[i+1].fi - forbidden[i].se);
	}
	printf("%.20f\n", ans);
	return 0;
}