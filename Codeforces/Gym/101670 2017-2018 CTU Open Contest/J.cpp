#include <bits/stdc++.h>
using namespace std;
#define MAXN 2000009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN], dist[MAXN];
int m, n;
//Vertices enumerados de 1 a m em U e de 1 a n em V!!!!

bool bfs() {
    queue<int> q;
    for (int u = 1; u <= m; u++) {
        if (pairU[u] == 0) {
            dist[u] = 0; q.push(u);
        }
        else dist[u] = INF;
    }
    dist[0] = INF;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist[u] >= dist[0]) continue;
        for (int i = 0; i < (int)adjU[u].size(); i++) {
            int v = adjU[u][i];
            if (dist[pairV[v]] == INF) {
                dist[pairV[v]] = dist[u] + 1;
                q.push(pairV[v]);
            }
        }
    }
    return (dist[0] != INF);
}

bool dfs(int u) {
    if (u == 0) return true;
    for (int i = 0; i < (int)adjU[u].size(); i++) {
        int v = adjU[u][i];
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

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int main() {
	int k;
	while(scanf("%d", &k) != EOF) {
		map<ii, int> odd, even;
		m = n = 0;
		FOR(i, k) {
			int x, y;
			scanf("%d %d", &x, &y);
			if ((x + y) % 2 == 0) even[{x, y}] = ++n;
			else {
				odd[{x, y}] = ++m;
				adjU[m].clear();
			}
		}
		for(auto pp : odd) {
			int x = pp.fi.fi;
			int y = pp.fi.se;
			int u = pp.se;
			FOR(k, 4) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (even.count({nx, ny})) adjU[u].pb(even[{nx, ny}]);
			}
		}
		printf("%d\n", n+m-hopcroftKarp());
	}
	return 0;
}