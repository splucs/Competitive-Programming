#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF (1LL<<60)

typedef long long ll;
typedef pair<ll, int> ii;
vector<ii> adjList[MAXN];
vector<int> rev[MAXN];
ll dist[MAXN];
int N, M, C;
bool client[MAXN];
 
void dijkstra(int s)
{
	for(int i=1; i<=N; i++) dist[i] = INF;
	dist[s]=0;
	set<ii> nodes;
	nodes.insert(ii(0, s));
	rev[s].clear();
	while(!nodes.empty()){
		int u = nodes.begin()->second;
		nodes.erase(nodes.begin());
		for(int i=0; i<(int)adjList[u].size(); i++){
			int v = adjList[u][i].second;
			ll w = adjList[u][i].first;
			if (dist[v] > dist[u] + w){
				rev[v].clear();
				if (dist[v] < INF){
					nodes.erase(ii(dist[v], v));
				}
				dist[v] = dist[u] + w;
				nodes.insert(ii(dist[v], v));
			}
			if (dist[v] == dist[u] + w) rev[v].push_back(u);
		}
	}
}


vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN];
int m, n;
///Vértices enumerados de 1 a m em U e de 1 a n em V!!!!
bool bfs()
{
    queue<int> q;
    for (int u=1; u<=m; u++){
        if (pairU[u]==0) {
            dist[u] = 0;
            q.push(u);
        }
        else dist[u] = INF;
    }
    dist[0] = INF;
    int u, v;
    while (!q.empty()){
        u = q.front(); q.pop();
        if (dist[u] < dist[0]){
            for (int i=0; i<(int)adjU[u].size(); ++i) {
                v = adjU[u][i];
                if (dist[pairV[v]] == INF){
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[0] != INF);
}

bool dfs(int u)
{
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i){
        v = adjU[u][i];
        if (dist[pairV[v]] == dist[u]+1){
            if (dfs(pairV[v])){
                pairV[v] = u; pairU[u] = v;
                return true;
            }
        }
    }
    dist[u] = INF;
    return false;
}

//O(E*sqrt(V))
int hopcroftKarp()
{
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    while (bfs()){
        for (int u=1; u<=m; u++){
            if (pairU[u]==0 && dfs(u))
                result++;
        }
    }
    return result;
}

set<int> reach[MAXN];
bool vis[MAXN];

void getreach(int u) {
	if (vis[u]) return;
	vis[u] = true;
	reach[u].insert(u);
	for(int i=0; i<(int)rev[u].size(); i++) {
		int v = rev[u][i];
		getreach(v);
		reach[u].insert(reach[v].begin(), reach[v].end());
	}
	for(set<int>::iterator it = reach[u].begin(); it!=reach[u].end(); it++) {
		int v = *it;
		if (u != v && client[v] && client[u]) {
			adjU[v].push_back(u);
			//printf("edge %d to %d\n", v, u);
		}
	}
}

int main() {
	int c;
	memset(&client, false, sizeof false);
	scanf("%d %d %d", &N, &M, &C);
	for(int i=1; i<=C; i++) {
		scanf("%d", &c);
		c++;
		client[c] = true;
	}
	client[1] = true;
	int u, v;
	ll w;
	for(int j=0; j<M; j++) {
		scanf("%d %d %lld", &u, &v, &w);
		u++; v++;
		adjList[u].push_back(ii(w, v));
	}
	dijkstra(1);
	memset(&vis, false, sizeof vis);
	for(int i=1; i<=N; i++) {
		getreach(i);
	}
	n = m = N;
	printf("%d\n", C-hopcroftKarp()+1);
	return 0;
}