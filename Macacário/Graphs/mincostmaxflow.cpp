#include <cstring>
#include <set>
using namespace std;
#define MAXN 100009
#define MAXM 900009
#define INFLL 0x3f3f3f3f3f3f3f3f
typedef long long ll;

/*
 * Min Cost Max Flow in O(VE(VlogV+E))
 */

int ned;
int first[MAXN], to[MAXM], nxt[MAXM], prv[MAXN];
ll cap[MAXM], cost[MAXM], dist[MAXN], pot[MAXN]; 

void init() {
	memset(first, -1, sizeof first);
	ned = 0;
}

void add(int u, int v, ll f, ll c) {
	to[ned] = v, cap[ned] = f;
	cost[ned] = c, nxt[ned] = first[u];
	first[u] = ned++;
	to[ned] = u, cap[ned] = 0;
	cost[ned] = -c, nxt[ned] = first[v];
	first[v] = ned++;
}

bool dijkstra(int s, int t, int n) {
	memset(&prv, -1, sizeof prv);
	for(int i = 1; i <= n; i++) dist[i] = INFLL;
	set< pair<ll, int> > q;
	q.insert(make_pair(0LL, s));
	dist[s] = prv[s] = 0;
	while(!q.empty()) {
		int u = q.begin()->second;
		q.erase(q.begin());
		for(int e = first[u]; e != -1; e = nxt[e]) {
			if (cap[e] <= 0) continue;
			int v = to[e];
			ll new_dist = dist[u] + cost[e] + pot[u] - pot[v];
			if (new_dist < dist[v]) {
				q.erase(make_pair(dist[v], v));
				dist[v] = new_dist;
				prv[v] = e;
				q.insert(make_pair(new_dist, v));
			}
		}
	}
	return prv[t] != -1;
}

ll augment(int s, int t, ll &maxflow, int n) {
	ll flow = maxflow;
	for(int i = t; i != s; i = to[prv[i]^1])
		flow = min(flow, cap[prv[i]]);
	for(int i = t; i != s; i = to[prv[i]^1]) {
		cap[prv[i]] -= flow;
		cap[prv[i]^1] += flow;
	}
	maxflow -= flow;
	ll flowCost = flow*(dist[t]-pot[s]+pot[t]);
	for(int i = 1; i <= n; i++)
		if (prv[i] != -1) pot[i] += dist[i];
	return flowCost;
}

ll mincostmaxflow(int s, int t, ll &maxflow, int n) {
	ll flowCost = 0;
	memset(pot, 0, sizeof pot);
	while(maxflow > 0 && dijkstra(s, t, n)) {
		flowCost += augment(s, t, maxflow, n);
	}
	return flowCost;
}

/*
 * Codeforces 101726I
 */

#include <cstdio>

int n, m;
int in[60], out[60];
bool reach[60][60];

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		ll ans = 0;
		scanf("%d %d", &n, &m);
		memset(&in, 0, sizeof in);
		memset(&out, 0, sizeof out);
		memset(&reach, false, sizeof reach);
		init();
		for(int j = 0; j < m; j++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			ans += w;
			add(u, v, INFLL, w);
			in[v]++;
			out[u]++;
			reach[u][v] = true;
		}
		for(int k = 1; k <= n; k++) {
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= n; j++) {
					reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
				}
			}
		}

		bool ok = true;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if (!reach[i][j]) ok = false;
			}
		}
		int s = n+1;
		int t = n+2;
		ll maxflow = 0;
		for(int u = 1; u <= n; u++) {
			int bal = in[u] - out[u];
			if (bal < 0) {
				add(u, t, -bal, 0);
			}
			if (bal > 0) {
				add(s, u, bal, 0);
				maxflow += bal;
			}
		}
		ll cost = mincostmaxflow(s, t, maxflow, n+2);
		if (maxflow > 0) ok = false;
		if (ok) printf("%lld\n", cost+ans);
		else printf("-1\n");
	}
	return 0;
}