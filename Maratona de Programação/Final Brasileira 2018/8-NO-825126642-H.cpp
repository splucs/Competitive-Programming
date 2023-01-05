#include <bits/stdc++.h>
#define INF 1000000009
#define EPS 1e-9
#define MAXN 100009
#define FOR(x,n) for(int x=0;x<n;x++)
#define FORN(x,i,n) for(int x=i;x<n;x++)
#define FOR1(x,n) for(int x=1;x<=n;x++)
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef pair<ii, int> iii;
ll MOD = 1000000007;

vector< pair<int, ii> > adjList[MAXN];
ll dst[MAXN];

void dijkstra(int s, int n) {
	FOR(i, n) dst[i] = INF*1ll*INF;
	set<pll> pq;
	dst[s] = 0;
	pq.insert(pll(0, s));
	while (!pq.empty()) {
		ll u = pq.begin()->second;
		pq.erase(pq.begin());
		FOR(i, sz(adjList[u])) {
			ll v = adjList[u][i].first;
			ll w = adjList[u][i].second.first;
			if (dst[v] > dst[u] + w) {
				pq.erase(pll(dst[v], v));
				dst[v] = dst[u] + w;
				pq.insert(pll(dst[v], v));
			}
		}
	}
}

bool taken[MAXN];

ll prim(int s) {
	mset(taken, false);
	taken[s] = true;
	priority_queue<pll> pq;
	pll front;
	ll cost = 0;
	FOR(j, sz(adjList[s])) {
		int v = adjList[s][j].fi;
		int w = adjList[s][j].se.se;
		int l = adjList[s][j].se.fi;
		if (dst[v] - dst[s] != l) continue;
		pq.push(pll(-w, -v));
	}
	while(!pq.empty()) {
		front = pq.top();
		pq.pop();
		int u = -front.se;
		int w = -front.fi;
		if (taken[u]) continue;
		cost += w;
		taken[u] = true;
		FOR(j, sz(adjList[u])) {
			int v = adjList[u][j].fi;
			int l = adjList[u][j].se.fi;
			int w = adjList[u][j].se.se;
			if (dst[v] - dst[u] != l) continue;
			if (!taken[v]) {
				pq.push(pll(-w, -v));
			}
		}
	}
	return cost;
}

int pai[MAXN];

int main() {
	int n, m, a, b, c, d;
	scanf("%d %d", &n, &m);
	
	FOR(i, m) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		a--; b--;
		adjList[a].pb({b, {c, d}});
		adjList[b].pb({a, {c, d}});
	}
	dijkstra(0, n);
	//FOR(i, n) printf("dst[%d] = %lld\n", i, dst[i]);
	printf("%lld\n", prim(0));
}

