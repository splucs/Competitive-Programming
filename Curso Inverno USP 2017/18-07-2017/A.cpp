using namespace std;
#define MAXN 103000
#define MAXM 900000
#include <bits/stdc++.h>
using namespace std;
#define INF (1LL << 60)
typedef long long ll;

int N, M, ned, prv[MAXN], first[MAXN];
ll cap[MAXM], cost[MAXM], to[MAXM], nxt[MAXM], dist[MAXN], pot[MAXN], K;

void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, ll f, ll c){
    to[ned] = v, cap[ned] = f;
    cost[ned] = c, nxt[ned] = first[u];
    first[u] = ned++;
    
    to[ned] = u, cap[ned] = 0;
    cost[ned] = -c, nxt[ned] = first[v];
    first[v] = ned++;
}

bool dijkstra(int s, int t){
    memset(prv, -1, sizeof prv);
    for(int i = 0; i < N; i++) dist[i] = INF;
    set< pair<ll, int> > q;
    q.insert(make_pair(0LL, s));
    dist[s] = prv[s] = 0;
    int u, v;
    while(!q.empty()){
        u = q.begin()->second;
        q.erase(q.begin());
        for(int e = first[u];e!=-1;e = nxt[e]){
            if(cap[e]<=0) continue;
            v = to[e];
            ll new_dist = dist[u] + cost[e] + pot[u] - pot[v];
            if(new_dist < dist[v]){
                q.erase(make_pair(dist[v], v));
                dist[v] = new_dist;
                prv[v] = e;
                q.insert(make_pair(new_dist, v));
            }
        }
    }
	if (prv[t] == -1) printf("no more path found\n");
	else printf("path with cost: %lld\n", dist[t]);
    return prv[t]!=-1;
}

ll augment(int s, int t){
    ll flow = K;
    for(int i = t; i != s; i = to[prv[i]^1])
        flow = min(flow,cap[prv[i]]);
    for(int i = t; i != s; i = to[prv[i]^1]){
        cap[prv[i]] -= flow;
        cap[prv[i]^1] += flow;
    }
    K -= flow;
    ll flowCost = flow*(dist[t]-pot[s]+pot[t]);
    for(int i = 0; i < N; i++)
        if (prv[i]!=-1) pot[i] += dist[i];
    return flowCost;
}

ll mincostmaxflow(int s, int t){
    ll flowCost = 0;
    memset(pot, 0, sizeof(pot));
    while(dijkstra(s, t)){
        flowCost = max(flowCost, augment(s, t));
    }
    return flowCost;
}

int main() {
	int T;
	ll c, C;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d %lld %lld", &N, &M, &K, &C);
		int s = 0;
		init();
		for(int i=1; i<=N; i++) {
			add(s, i, 1, 0);
			for(int j=1; j<=M; j++) {
				scanf("%lld", &c);
				add(i, N+j, 1, c);
				add(i, N+M+j, 1, c+C);
			}
		}
		int t = N+2*M+1;
		for(int j=1; j<=M; j++) {
			add(N+j, t, 1, 0);
			add(N+M+j, t, 1, 0);
		}
		N = N+2*M+2;
		printf("%lld\n", mincostmaxflow(s, t));
		printf("K=%lld\n", K);
	}
	return 0;
}