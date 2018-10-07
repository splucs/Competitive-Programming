#include <bits/stdc++.h>
#define FOR(x, n) for(int x=0; x<n; x++)
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define INF 1000000009
#define MAXN 1000009
using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

ll acum[MAXN], sum[MAXN];

ll solve(vector<ii> &a, vector<ii>& b, vector<ii>& c, int d) {
	ll ans = 0;
	
	int other = 0;
	FOR(i, sz(c)) {
		while (other < sz(b) && b[other] < c[i]) other++;
		sum[i] = other;
		acum[i] = sum[i];
		if (i > 0) acum[i] += acum[i-1];
	}

	FOR(i, sz(a)) {
		int z = lower_bound(all(b), a[i]) - b.begin();
		if (z == sz(b)) continue;

		int p = lower_bound(all(c), ii(a[i].first + d, INF)) - c.begin();
		p--; if (p < 0 || c[p] < a[i]) continue;

		int q1 = lower_bound(all(c), b[z]) - c.begin();
		int q2 = lower_bound(all(c), a[i]) - c.begin();
		int q = max(q1, q2);
		if (p < q) continue;

		ans += acum[p] -(p-q+1)*1LL*(z)- ((q == 0) ? 0 : (acum[q-1]));
	//	printf("(%d %d %d) %d %d %d %lld %lld %lld\n", a[i].first, b[z].first, c[p].first, i, p, q, acum[p], acum[q], ans);
	}
	//printf("%lld\n", ans);
	return ans;
}

int main() {
	int d, na, nb, nc;
	while (scanf("%d %d %d %d", &d, &na, &nb, &nc) != EOF) {
		vector<ii> a(na), b(nb), c(nc);
		int cnt = 0;
		FOR(i, na) { scanf("%d", &a[i].first); a[i].second = ++cnt; }
		FOR(i, nb) { scanf("%d", &b[i].first); b[i].second = ++cnt; }
		FOR(i, nc) { scanf("%d", &c[i].first); c[i].second = ++cnt; }

		ll ans = 0;
		ans += solve(a, b, c, d);
		ans += solve(a, c, b, d);
		ans += solve(b, a, c, d);
		ans += solve(b, c, a, d);
		ans += solve(c, a, b, d);
		ans += solve(c, b, a, d);
		
		printf("%lld\n", ans);
	}
}