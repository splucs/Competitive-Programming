#include <cstdio>
#include <climits>
#include <cstring>
#include <queue>
#include <set>

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

int main(){
    int Nl,u[5000],v[5000], M;
    ll c[5000],D;
    
    while(scanf("%d %d",&Nl,&M)==2){
        N = 2*Nl+1;
        
        for(int i = 0;i<M;++i){
            scanf("%d %d %lld",&u[i],&v[i],&c[i]);
            --u[i]; --v[i];
        }
        scanf("%lld %lld",&K,&D);
        
        init();
        add(0,1,K,0);
        
        for(int i = 0;i<Nl;++i) add(1+2*i,1+2*i+1,INF,0);
        
        for(int i = 0;i<M;++i){
            add(1+2*u[i]+1,1+2*v[i],D,c[i]);
            add(1+2*v[i]+1,1+2*u[i],D,c[i]);
        }
        
        D = mincostmaxflow(0,2*Nl-1);
        
        if(K > 0) printf("Impossible.\n");
        else printf("%lld\n", D);
    }
    
    return 0;
}