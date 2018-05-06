#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF (1LL<<60)
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<ll, ll> ii;

int N;
ll L, R;
map<ll, vector<ii> > lines;
vector<pair<ll, ll> > f;

ll xt[MAXN], xb[MAXN], yt[MAXN], yb[MAXN];

ii get(ll s, int j) {
	ll l = max((s-xt[j]), yb[j]);
	ll r = min((s-xb[j]), yt[j]);
	return ii(l, r);
}

int main() {
	while(scanf("%d %lld %lld", &N, &L, &R) != EOF) {
		FOR(i, N) {
			scanf("%lld %lld %lld %lld", &xb[i], &yb[i], &xt[i], &yt[i]);
		}
		lines.clear(); f.clear();
		FOR(i, N) FOR(j, N) {
			vector<ll> x, y;
			x.pb(xb[i]); x.pb(xb[j]); x.pb(xt[i]); x.pb(xt[j]);
			y.pb(yb[i]); y.pb(yb[j]); y.pb(yt[i]); y.pb(yt[j]);
			for(ll xt : x) for(ll yt : y) {
				ll s = xt+yt;
				ii cur = get(s, i);
				if (cur.second >= cur.first) lines[s].pb(cur);
				cur = get(s, j);
				if (cur.second >= cur.first) lines[s].pb(cur);
			}
		}
		for(auto & pp : lines) {
			vector<ii> & v = pp.second;
			sort(all(v));
			ll last = -INF;
			ll cur = 0;
			for(ii & pr : v) {
				pr.first = max(pr.first, last);
				last = max(last, pr.second);
				if (pr.second >= pr.first)
					cur += pr.second - pr.first;
			}
			f.pb({pp.first, cur});
			//printf("f(%lld) = %lld\n", pp.first, cur);
		}
		ll ans = 0;
		ll last = -INF;
		FOR(i, int(f.size())) {
			if (i == 0) continue;
			ll a = f[i-1].first, b = f[i].first;
			ll fa = f[i-1].second, fb = f[i].second;
			
			ll l = max(L, a);
			l = max(l, last+1);
			ll fl = fa + ((fb-fa)/(b-a))*(l - a);
			
			ll r = min(R, b);
			ll fr = fa + ((fb-fa)/(b-a))*(r - a);
			last = max(last, r);
			
			if(r >= l) {
				ans += ((fl+fr)*(r-l+1))/2;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
