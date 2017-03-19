#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define MAXN 1009

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN];
bool vis[MAXN];
int m, n;

bool dfs(int u)
{
	vis[u] = true;
	if (u == 0) return true;
	int v;
	for (int i = 0; i != (int)adjU[u].size(); ++i) {
		v = adjU[u][i];
		if (!vis[pairV[v]] && dfs(pairV[v])) {
			pairV[v] = u; pairU[u] = v;
			return true;
		}
	}
	return false;
}

int hungarian()
{
	memset(&pairU, 0, sizeof pairU);
	memset(&pairV, 0, sizeof pairV);
	int result = 0;
	for (int u = 1; u <= m; u++) {
		memset(&vis, false, sizeof vis);
		if (pairU[u] == 0 && dfs(u))
			result++;
	}
	return result;
}