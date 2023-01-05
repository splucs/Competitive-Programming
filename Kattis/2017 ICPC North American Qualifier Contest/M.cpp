#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define INF 1e9
#define MAXX 1000
typedef long long ll;
typedef pair<ll, ll> ii;

int n, k;
ll cx[MAXN], cy[MAXN], b[MAXN];

inline ll cub(ll x) {
	return abs(x*x*x);
}

ii getbounds(ll x, int i) {
	if (cub(x-cx[i]) > b[i]) return ii(INF, -INF);
	ll y1, y2;
	ll hi = n+1;
	ll lo = cy[i];
	while(hi > lo + 1) {
		ll y = (hi+lo)/2;
		if (cub(x-cx[i]) + cub(y-cy[i]) <= b[i]) lo = y;
		else hi = y;
	}
	y2 = lo;
	hi = cy[i];
	lo = -1;
	while(hi > lo + 1) {
		ll y = (hi+lo)/2;
		if (cub(x-cx[i]) + cub(y-cy[i]) <= b[i]) hi = y;
		else lo = y;
	}
	y1 = hi;
	return ii(y1, y2);
}

map<ll, vector<ii> > usedx;

int main(){
	scanf("%d %d", &n, &k);
	for (int i=0; i<k; i++){
		scanf("%lld %lld %lld", &cx[i], &cy[i], &b[i]);
	}
	for (int i=0; i<k; i++){
		for (ll x=cx[i]-MAXX; x<=cx[i]+MAXX; x++){
			ii inter = getbounds(x, i);
			if (inter.first > inter.second) continue;
			usedx[x].push_back(inter);
		}
	}
	ll ans = 0;
	for(map<ll, vector<ii> >::iterator it = usedx.begin(); it != usedx.end(); it++) {
		vector<ii> & v = it->second;
		sort(v.begin(), v.end());
		ll tot = n;
		ll last = -1;
		for(int i=0; i<(int)v.size(); i++) {
			//printf("%lld to %lld\n", v[i].first, v[i].second);
			v[i].first = max(v[i].first, last+1);
			if (v[i].first > v[i].second) continue;
			ans += v[i].second - v[i].first + 1;
			last = max(last, v[i].second);
		}
	}
	ans = (n+1)*1ll*(n+1) - ans;
	printf("%lld\n", ans);
	return 0;
}