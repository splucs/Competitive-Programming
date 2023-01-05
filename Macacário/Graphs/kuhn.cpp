#include <vector>
#include <queue>
#include <cstring>
#define MAXN 1009
using namespace std;

/*
 * Kuhn's Algorithm O(VE)
 */

vector<int> adjU[MAXN];
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

int kuhn() {
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
		while(scanf("%d", &v), v) adjU[u].push_back(v);
	}
	printf("%d\n", kuhn());
	for (int u = 1; u <= m; u++) {
		if (pairU[u]) printf("%d %d\n", u, pairU[u]);
	}
	return 0;
}