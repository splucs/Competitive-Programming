#include <bits/stdc++.h>
using namespace std;
#define MAXN 1109
#define INF (1<<30)

int N;
bool win[MAXN][MAXN], elim[MAXN], par[MAXN];
int good[MAXN], bad[MAXN], rest[MAXN], restcnt, alive[MAXN];

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN], dist[MAXN];
int m, n;

//Vértices enumerados de 1 a m em U e de 1 a n em V!!!!
bool bfs() {
    queue<int> q;
    for (int u=1; u<=m; u++) {
        if (pairU[u]==0) {
            dist[u] = 0;
            q.push(u);
        }
        else dist[u] = INF;
    }
    dist[0] = INF;
    int u, v;
    while (!q.empty()) {
        u = q.front(); q.pop();
        if (dist[u] < dist[0]) {
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

bool dfs(int u) {
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i) {
        v = adjU[u][i];
        if (dist[pairV[v]] == dist[u]+1) {
            if (dfs(pairV[v])) {
                pairV[v] = u; pairU[u] = v;
                return true;
            }
        }
    }
    dist[u] = INF;
    return false;
}

//O(E*sqrt(V))
int hopcroftKarp() {
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    while (bfs()) {
        for (int u=1; u<=m; u++) {
            if (pairU[u]==0 && dfs(u))
                result++;
        }
    }
    return result;
}

char buffer[MAXN];

int main() {
	while(scanf(" %d", &N) != EOF) {
		for(int i=1; i<=N; i++) {
			elim[i] = false;
			scanf(" %s", buffer);
			for(int j=1; j<=N; j++) {
				if (buffer[j-1] == '1') win[i][j] = true;
				else win[i][j] = false;
			}
		}
		
		int alivecnt = 0;
		for(int i=0; i<N; i++) alive[alivecnt++] = i+1;
		memset(&elim, false, sizeof elim);
		for(int mt = N/2; mt>0; mt>>=1) {		
			
			m = n = 0;
			for(int i=0; i<alivecnt; i++) {
				int u = alive[i];
				par[u] = false;
				if (u == 1) continue;
				if (!elim[u] && win[1][u]) good[++m] = u;
				if (!elim[u] && !win[1][u]) bad[++n] = u;
			}
			
			for(int i=1; i<=m; i++) {
				adjU[i].clear();
				for(int j=1; j<=n; j++) {
					if (win[good[i]][bad[j]]) {
						adjU[i].push_back(j);
					}
				}
			}
			
			hopcroftKarp();
			for(int i=1; i<=m; i++) {
				if (pairU[i] != 0) {
					int u = good[i], v = bad[pairU[i]];
					printf("%d %d\n", u, v);
					par[u] = true; par[v] = true;
					elim[v] = true;
				}
			}
			
			for(int i=0; i<alivecnt; i++) {
				int u = alive[i];
				if (!elim[u] && !par[u] && win[1][u]) {
					printf("%d %d\n", 1, u);
					par[1] = true; par[u] = true;
					elim[u] = true;
					break;
				}
			}
			
			restcnt = 0;
			for(int i=0; i<alivecnt; i++) {
				int u = alive[i];
				if (!elim[u] && !par[u] && win[u][1]) rest[restcnt++] = u;
			}
			for(int i=0; i<alivecnt; i++) {
				int u = alive[i];
				if (!elim[u] && !par[u] && !win[u][1]) rest[restcnt++] = u;
			}
			for(int it=0; it+1<restcnt; it+=2) {
				int u = rest[it];
				int v = rest[it+1];
				if (win[v][u]) swap(u, v);
				printf("%d %d\n", u, v);
				par[u] = par[v] = true;
				elim[v] = true;
			}
			
			int k=0;
			for(int i=0; i<alivecnt; i++) {
				int u = alive[i];
				if (!elim[u]) alive[k++] = u;
			}
			alivecnt = k;
		}
	}
}