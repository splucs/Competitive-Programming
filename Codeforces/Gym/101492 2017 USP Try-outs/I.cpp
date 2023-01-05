#include <bits/stdc++.h>
using namespace std;
#define MAXN 103000
#define MAXM 900000
#define INF (1LL << 60)
typedef long long ll;

int N, ned, prv[MAXN], first[MAXN];
ll cap[MAXM], cost[MAXM], to[MAXM], nxt[MAXM], dist[MAXN], pot[MAXN], K;

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

bool dijkstra(int s, int t) {
	memset(prv, -1, sizeof prv);
	for(int i = 0; i < N; i++) dist[i] = INF;
	set< pair<ll, int> > q;
	q.insert(make_pair(0LL, s));
	dist[s] = prv[s] = 0;
	int u, v;
	while(!q.empty()) {
		u = q.begin()->second;
		q.erase(q.begin());
		for(int e = first[u];e!=-1;e = nxt[e]) {
			if(cap[e]<=0) continue;
			v = to[e];
			ll new_dist = dist[u] + cost[e] + pot[u] - pot[v];
			if(new_dist < dist[v]) {
				q.erase(make_pair(dist[v], v));
				dist[v] = new_dist;
				prv[v] = e;
				q.insert(make_pair(new_dist, v));
			}
		}
	}
	return prv[t]!=-1;
}

ll augment(int s, int t) {
	ll flow = K;
	for(int i = t; i != s; i = to[prv[i]^1])
		flow = min(flow,cap[prv[i]]);
	for(int i = t; i != s; i = to[prv[i]^1]) {
		cap[prv[i]] -= flow;
		cap[prv[i]^1] += flow;
	}
	K -= flow;
	ll flowCost = flow*(dist[t]-pot[s]+pot[t]);
	for(int i = 0; i < N; i++)
		if (prv[i]!=-1) pot[i] += dist[i];
	return flowCost;
}

ll mincostmaxflow(int s, int t) {
	ll flowCost = 0;
	memset(pot,0,sizeof(pot));
	while(dijkstra(s, t)) {
		flowCost += augment(s, t);
	}
	return flowCost;
}

const ll M = 1000000;
int last[MAXN], cnt[MAXN];

int main() {
	init();
	N = 0;
	int s = N++;
	int t = N++;
	int n, m, b;
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++) {
		last[i] = N++;
		scanf("%d", &b);
		add(s, last[i], INF, M-b);
	}
	for(int j=0; j<=m; j++) {
		for(int k=0; k<N; k++) {
			cnt[k] = 0;
		}
		
		int l, r, k1, k2;
		if (j<m) k1=N++, k2=N++;
		else k1=N++, k2=t;
		ll c;
		
		if (j<m) scanf("%d %d %I64d", &l, &r, &c);
		else l=1, r=N, c=INF;
		add(k1, k2, c, 0);
		
		for(int i=l; i<=r; i++) {
			cnt[last[i]]++;
			last[i] = k2;
		}
		for(int k=0; k<N; k++) {
			if (cnt[k] > 0) {
				add(k, k1, cnt[k], 0);
			}
		}
	}
	
	K = INF;
	ll mc = mincostmaxflow(s, t);
	K = INF - K;
	printf("flow sent = %I64d\n", K);
	printf("%I64d", mc);
	return 0;
}