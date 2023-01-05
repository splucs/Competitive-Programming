#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 100009
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<ll, int> ii;

vector<ii> g[MAXN];
int n, m;

void dijkstra(vector<int> s, ll dist[]) {
	FOR(i, n) dist[i] = INFLL;
	set<ii> pq;
	for(int u : s) {
		dist[u] = 0;
		pq.insert({dist[u], u});
	}
	while(!pq.empty()) {
		int u = pq.begin()->se;
		pq.erase(pq.begin());
		for (ii pp : g[u]) {
			ll w = pp.fi;
			int v = pp.se;
			if (dist[v] > dist[u] + w) {
				pq.erase({dist[v], v});
				dist[v] = dist[u] + w;
				pq.insert({dist[v], v});
			}
		}
	}
}

ll distD[MAXN], distP[MAXN];

int main() {
	scanf("%d %d", &n, &m);
	FOR(j, m) {
		int u, v; ll w;
		scanf("%d %d %lld", &u, &v, &w);
		g[u].pb({w, v});
		g[v].pb({w, u});
	}
	vector<int> police;
	vector<int> destiny;
	vector<int> queries;
	int k;
	scanf("%d", &k);
	while(k --> 0) {
		int u; scanf("%d", &u);
		police.pb(u);
	}
	int q;
	scanf("%d", &q);
	while(q --> 0) {
		int u; scanf("%d", &u);
		queries.pb(u);
	}
	int s, d;
	scanf("%d %d", &s, &d);
	destiny.pb(d);
	dijkstra(destiny, distD);
	dijkstra(police, distP);
	ll minthief = 2*distD[s];
	ll minpolice = 2*distP[d];
	for(int u : queries) {
		minpolice = min(minpolice, 2*distP[u] + distD[u]);
	}
	ll ans = minthief/2;
	if (minpolice <= minthief) ans = -1;
	printf("%lld\n", ans);
	return 0;
}