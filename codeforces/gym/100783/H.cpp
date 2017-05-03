#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define MAXM 10009
#define INF (1LL<<60)
 
typedef long long ll;
typedef pair<ll, int> ii;
vector<ii> adjList[MAXN];
ll dist[MAXN], pdist[MAXN];
int n, N, M, X, Y, pos[MAXN][2];
set<int> S;
int eu[MAXM], ev[MAXM];
ll dO[MAXN], dT[MAXN], ew[MAXM];

void bellmanford(int s){
	for(int i=1; i<=n; i++){
		pdist[i] = dist[i] = INF;
	}
	pdist[s] = dist[s] = 0;
	ll w;
	dO[0] = dT[0] = INF;
	for (int c = 1, v; c < N; c++){
		for (int u = 1; u <= n; u++) {
			for (int j = 0; j < (int)adjList[u].size(); j++) {
				v = adjList[u][j].second;
				w = adjList[u][j].first;
				dist[v] = min(dist[v], pdist[u] + w);
			}
			pdist[u] = dist[u];
		}
		dO[c] = pdist[pos[Y][1]];
		dT[c] = pdist[pos[Y][0]];
	}
}
 
int main(){
	int L, l;
	scanf("%d %d %d %d", &N, &M, &X, &Y);
	for(int i=0; i<M; i++){
		scanf("%d %d %I64d", &eu[i], &ev[i], &ew[i]);
	}
	scanf("%d", &L);
	while(L--){
		scanf("%d", &l);
		S.insert(l);
	}
	n=0;
	for(int i=1; i<=N; i++){
		for(int k=0; k<2; k++){
			pos[i][k] = ++n;
		}
	}
	for(int i=0; i<M; i++){
		int u = eu[i], v = ev[i];
		ll w = ew[i];
		adjList[pos[u][1]].push_back(ii(w, pos[v][S.count(v)]));
		adjList[pos[u][0]].push_back(ii(w, pos[v][0]));
		swap(u, v);
		adjList[pos[u][1]].push_back(ii(w, pos[v][S.count(v)]));
		adjList[pos[u][0]].push_back(ii(w, pos[v][0]));
	}
	bellmanford(pos[X][1]);
	int A, B;
	for(int c=N-1; c>=0; c--){
		if (dO[c] < INF){
			//printf("dO: %I64d + C*%d\n", dO[c], c);
			A = c;
		}
		if (dT[c] < INF){
			//printf("dT: %I64d + C*%d\n", dT[c], c);
			B = c;
		}
	}
	if (A < B || (A==B && dO[A] < dT[B])){
		printf("Infinity\n");
		return 0;
	}
	ll ans = -1, cur;
	for(int ci = 0; ci<N; ci++) {
		if (dO[ci] == INF) continue;
		ll maxC = INF;
		ll minC = 0;
		for(int cj = 0; cj<N; cj++) {
			if (dT[cj] == INF) continue;
			if (ci > cj){
				maxC = min(maxC, (dO[ci]-dT[cj])/(cj-ci) - ((dO[ci]-dT[cj])%(cj-ci) == 0 ? 1 : 0));
			}
			else if (ci < cj){
				minC = max(minC, (dO[ci]-dT[cj])/(cj-ci) + 1);
			}
			else{
				if (dO[ci] >= dT[cj]) minC = maxC + 1;
			}
		}
		ans = max(ans, maxC);
	}
	if (ans <= 0) printf("Impossible\n");
	else printf("%I64d\n", ans);
	return 0;
}