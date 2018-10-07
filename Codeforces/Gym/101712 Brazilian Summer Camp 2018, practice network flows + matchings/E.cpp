#include <vector>
#include <queue>
#include <cstring>
#define INF 0x3f3f3f3f
#define MAXN 1009
using namespace std;

/*
 * Hungarian algorithm O(VE)
 */

vector<int> adjU[MAXN], adjV[MAXN];
int pairU[MAXN], pairV[MAXN];
bool vis[MAXN];
int m, n;
///Vertices enumerados de 1 a m em U e de 1 a n em V!!!!

bool dfs(int u) {
    vis[u] = true;
    if (u == 0) return true;
    for (int i = 0; i < (int)adjU[u].size(); i++) {
        int v = adjU[u][i];
        if (!vis[pairV[v]] && dfs(pairV[v])) {
            pairV[v] = u; pairU[u] = v;
            return true;
        }
    }
    return false;
}

int hungarian() {
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    for (int u = 1; u <= m; u++) {
        memset(&vis, false, sizeof vis);
        if (pairU[u]==0 && dfs(u)) result++;
    }
    return result;
}

/*
 * Codeforces 101712A
 */

#include <cstdio>

int main() {
	scanf("%d %d", &m, &n);
	for (int u = 1; u <= m; u++) {
		int v;
		while(scanf("%d", &v), v) {
			adjU[u].push_back(v);
			adjV[v].push_back(u);
		}
	}
	int flow = -hungarian();
	for (int u = 1; u <= m; u++) if (!adjU[u].empty()) flow++;
	for (int v = 1; v <= n; v++) if (!adjV[v].empty()) flow++;
	printf("%d\n", flow);
	for (int u = 1; u <= m; u++) {
		if (pairU[u]) printf("%d %d\n", u, pairU[u]);
		else if (!adjU[u].empty()) printf("%d %d\n", u, adjU[u][0]);
	}
	for (int v = 1; v <= n; v++) {
		if (pairV[v]) continue;
		else if (!adjV[v].empty()) printf("%d %d\n", adjV[v][0], v);
	}
	return 0;
}