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

bool spfa(int s, int t){
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

ll suurballe(int s, int t){
    ll flowCost = 0;
    memset(pot,0,sizeof(pot));
    K = 2;
    if(spfa(s, t)) flowCost += augment(s, t);
    else return -1;
    if(spfa(s, t)) flowCost += augment(s, t);
    else return -1;
    return flowCost;
}

int main(){
    int u, v;
    ll w, ans;
    while(scanf("%d", &N), N){
        scanf("%d", &M);
        init();
        for(int i=0; i<M; i++){
            scanf("%d %d %lld", &u, &v, &w);
            add(u-1, v-1, 1, w);
            add(v-1, u-1, 1, w);
        }
        ans = suurballe(0, N-1);
        if (ans >= 0) printf("%lld\n", ans);
        else printf("Pernoite.\n");
    }
    return 0;
}