#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXB 309
#define MAXN MAXB*MAXB
using namespace std;

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

int ver[MAXB][MAXB], hor[MAXB][MAXB];
char board[MAXB][MAXB];

int main(){
	int T, N, M;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d", &N, &M);
		n = m = 0;
		for(int i=0; i<MAXN; i++) adjU[i].clear();
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				scanf(" %c", &board[i][j]);
				if (board[i][j] == 'A') {
					ver[i][j] = hor[i][j] = -1;
				}
				else {
					if (i > 0 && ver[i-1][j] != -1) ver[i][j] = ver[i-1][j];
					else ver[i][j] = ++m;
					if (j > 0 && hor[i][j-1] != -1) hor[i][j] = hor[i][j-1];
					else hor[i][j] = ++n;
					if (board[i][j] == 'H') adjU[ver[i][j]].push_back(hor[i][j]);
				}
			}
		}
		printf("%d\n", hopcroftKarp());
	}
	return 0;
}