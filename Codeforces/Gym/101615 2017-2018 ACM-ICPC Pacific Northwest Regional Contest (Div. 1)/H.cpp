#include <bits/stdc++.h>
#define MAXN 200009
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define REP(x,n) for(int x=n-1; x>=0; x--)
#define REP1(x,n) for(int x=n; x>0; x--)
#define pb push_back
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
typedef vector<int> vi;

struct CHT {
	vector<ll> m, n;
	vector<double> p;
	void clear() {
		m.clear();
		n.clear();
		p.clear();
	}
	double inter(double nm, double nn, double lm, double ln) {
		return (ln-nn)/(nm-lm);
	}
	void push(ll nm, ll nn) {
		while(!p.empty()) {
			if (nm == m.back() && nn >= n.back()) return;
			double x = inter(nm, nn, m.back(), n.back());
			if (nm != m.back() && p.back() < x) break;
			m.pop_back();
			n.pop_back();
			p.pop_back();
		}
		p.pb(p.empty() ? -INFLL : inter(nm, nn, m.back(), n.back()));
		m.pb(nm);
		n.pb(nn);
	}
	ll query(ll x) {
		if (p.empty()) return INFLL;
		int r = sz(p), l = 0;
		while(r > l+1) {
			int m = (l + r) / 2;
			if (x < p[m]) r = m;
			else l = m;
		}
		return m[l]*x + n[l];
	}
};

CHT cht[MAXN];

struct event {
	ll time;
	bool is_arrival;
	int j;
};

bool operator < (event a, event b) {
	if (a.time != b.time) return a.time < b.time;
	if (a.is_arrival != b.is_arrival) return a.is_arrival;
	return a.j < b.j;
}

struct flight {
	int from, to;
	ll s, t;
};

flight f[MAXN];
ll dp[MAXN];

void departure(int j) {
	flight cur = f[j];
	dp[j] = cur.s*cur.s + cht[cur.from].query(cur.s);
}

void arrival(int j) {
	flight cur = f[j];
	cht[cur.to].push(-2*cur.t, cur.t*cur.t + dp[j]);
}

int main() {
	int n, m;
	while(scanf("%d %d", &n, &m) != EOF) {

		FOR1(i, n) cht[i].clear();
		cht[1].push(0, 0);
		set<event> pq;

		FOR1(j, m) {
			scanf("%d %d %lld %lld", &f[j].from, &f[j].to, &f[j].s, &f[j].t);
			event ev;

			ev.time = f[j].s;
			ev.is_arrival = false;
			ev.j = j;
			pq.insert(ev);

			ev.time = f[j].t;
			ev.is_arrival = true;
			ev.j = j;
			pq.insert(ev);
		}

		for(event ev : pq) {
			if (ev.is_arrival) arrival(ev.j);
			else departure(ev.j);
		}

		ll ans = INFLL;
		FOR1(j, m) {
			if (f[j].to == n) ans = min(ans, dp[j]);
		}

		printf("%lld\n", ans);
	}
	return 0;
}