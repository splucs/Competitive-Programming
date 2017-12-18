#include <bits/stdc++.h>
using namespace std;
#define MAXN 259
#define INF (1<<30)

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

int K;
int xu[MAXN], xv[MAXN], yu[MAXN], yv[MAXN];

bool check(double t) {
	for(int u = 1; u <= m; u++) {
		adjU[u].clear();
		for(int v = 1; v <= n; v++) {
			if (hypot(xu[u]*1.0-xv[v], yu[u]*1.0-yv[v]) <= t) {
				adjU[u].push_back(v);
			}
		}
	}
	return hopcroftKarp() >= K;
}

int main() {
	scanf("%d %d %d", &m, &n, &K);
	for(int u = 1; u <= m; u++) {
		scanf("%d %d", &xu[u], &yu[u]);
	}
	for(int v = 1; v <= n; v++) {
		scanf("%d %d", &xv[v], &yv[v]);
	}
	double hi = 1e+9;
	double lo = 0;
	while(fabs(hi-lo) > 1e-9) {
		double t = (hi + lo) / 2;
		if (check(t)) hi = t;
		else lo = t;
	}
	printf("%.0f\n", hi*hi);
	return 0;
}