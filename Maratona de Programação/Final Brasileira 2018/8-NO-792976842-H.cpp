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

vector<pll> adjList[MAXN];
ll dst[MAXN];

void dijkstra(int s, int n) {
	FOR(i, n) dst[i] = 1ll*INF*INF;
	set<pll> pq;
	dst[s] = 0;
	pq.insert(pll(0, s));
	while (!pq.empty()) {
		ll u = pq.begin()->second;
		pq.erase(pq.begin());
		FOR(i, sz(adjList[u])) {
			ll v = adjList[u][i].second;
			ll w = adjList[u][i].first;
			if (dst[v] > dst[u] + w) {
				pq.erase(pll(dst[v], v));
				dst[v] = dst[u] + w;
				pq.insert(pll(dst[v], v));
			}
		}
	}
}

int pai[MAXN];

int find(int u) {
	while (pai[u] != u) {
		pai[u] = pai[pai[u]];
		u = pai[u];
	}
	return u;
}

bool unite(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b) return false;
	pai[a] = b;
	return true;
}

vector<pair<ii, ii> > edge;

int main() {
	int n, m, a, b, c, d;
	scanf("%d %d", &n, &m);
	FOR(i, n) pai[i] = i;
	
	FOR(i, m) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		a--; b--;
		edge.pb(make_pair(ii(d, c), ii(a, b)));
		adjList[a].pb(pll(c, b));
		adjList[b].pb(pll(c, a));
	}
	ll ans = 0;
	sort(edge.begin(), edge.end());
	dijkstra(0, n);
	FOR(i, m) {
		tie(d, c) = edge[i].first;
		tie(a, b) = edge[i].second;
		
		if (dst[a] + c == dst[b] || dst[a] == dst[b] + c) {
			if (unite(a, b)) ans += d;
		}
	}
	
	printf("%lld\n", ans);
}

