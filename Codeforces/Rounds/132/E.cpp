#include <bits/stdc++.h>
using namespace std;
#define MAXN 103000
#define MAXM 900000
#define MAXP 259
#define INF (1LL << 60)
typedef long long ll;

int N, ned, prv[MAXN], first[MAXN];
ll cap[MAXM], cost[MAXM], to[MAXM], nxt[MAXM], dist[MAXN], pot[MAXN], K;
ll capbackup[MAXM];

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
    memset(pot,0,sizeof(pot));
    while(dijkstra(s, t)){
        flowCost += augment(s, t);
    }
    return flowCost;
}

map<int, int> x2id;
int xcnt = 0, xinv[MAXP];
int reduce(int x) {
	if (!x2id.count(x)) {
		x2id[x] = xcnt;
		xinv[xcnt] = x;
		printf("xinv[%d] = %d\n", xcnt, x);
		xcnt++;
	}
	return x2id[x];
}

int arr[MAXN], M, V;
int pos[MAXP][MAXP];
int value[MAXN];
vector<char> pres[MAXP];

void printcost1edges(int u) {
	for(int e = first[u];e!=-1;e = nxt[e]){
		int v = to[e];
		for(ll it = cap[e]; it < capbackup[e] && cost[e] == 1LL; it++) {
			//printf("it = %I64d\n", it);
			printf("%c=%d (%d,%d)\n", pres[value[u]].back(), xinv[value[v]], value[u], value[v]);
			pres[value[v]].push_back(pres[value[u]].back());
			pres[value[u]].pop_back();
		}
	}
}

int main() {
	scanf("%d %d", &M, &V);
	reduce(0);
	arr[0] = -1;
	for(int m=1, x; m<=M; m++) {
		scanf("%d", &x);
		arr[m] = reduce(x);
	}
	
	N = 0;
	int s = N++, auxs = N++;
	int t = N++, auxt = N++;
	value[s] = value[auxs] = value[auxt] = value[t] = 0;
	for(int m=1, x; m<=M; m++) {
		for(int i=1; i<MAXP; i++) {
			pos[m][i] = N++;
			value[N-1] = i;
		}
	}
	
	init();
	add(s, auxs, V, 0);
	for(int i=1; i<MAXP; i++) {
		add(auxs, pos[1][i], INF, 1);
	}
	for(int m=1, x; m<=M; m++) {
		x = arr[m];
		
		add(pos[m][x], t, 1, 0);
		for(int i=1; i<MAXP; i++) {
			if (m < M) {
				add(pos[m][i], pos[m+1][i], INF, 0);
				add(pos[m][i], pos[m+1][arr[m+1]], INF, 1);
			}
			else {
				add(pos[m][i], auxt, INF, 0);
			}
			add(s, pos[m][i], 1, i == x ? 0 : 1);
		}
	}
	add(auxt, t, V, 0);
	
	K = V+M;
	for(int e=0; e<ned; e++) capbackup[e] = cap[e];
	ll mcost = mincostmaxflow(s, t);
	printf("%I64d %I64d\n", mcost+M, mcost);
	
	for(char c='a'; c<V+'a'; c++) {
		pres[0].push_back(c);
	}
	for(int m=1; m<=M; m++) {
		int x = arr[m];
		for(int i=1; i<MAXP; i++) {
			int u = pos[m][i];
			printcost1edges(u);
		}
		printf("print(%c)\n", pres[x].back());
	}
	
	return 0;
}