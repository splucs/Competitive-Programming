#include <vector>
#include <cstring>
#define INF 0x3f3f3f3f
#define MAXN 4009
using namespace std;

/*
 * Minimum Vertex Cover from Maximum Matching O(V+E)
 */

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN];
int m, n;
///Vértices enumerados de 1 a m em U e de 1 a n em V!!!!
bool Zu[MAXN], Zv[MAXN];
vector<int> coverU, coverV;

void getreach(int u) {
	if (u == 0 || Zu[u]) return;
	Zu[u] = true;
	for (int i = 0; i < (int)adjU[u].size(); i++) {
		int v = adjU[u][i];
		if (v == pairU[u]) continue;
		Zv[v] = true;
		getreach(pairV[v]);
	}
}

void minimumcover() {
	memset(&Zu, false, sizeof Zu);
	memset(&Zv, false, sizeof Zv);
	for (int u = 1; u <= m; u++)
		if (pairU[u] == 0) getreach(u);
	coverU.clear(); coverV.clear();
	for (int u = 1; u <= m; u++)
		if (!Zu[u]) coverU.push_back(u);
	for (int v = 1; v <= n; v++)
		if (Zv[v]) coverV.push_back(v);
}

/*
 * Codeforces 101712D
 */

#include <cstdio>

int main() {
	scanf("%d %d", &m, &n);
	for (int u = 1; u <= m; u++) {
		int k, v;
		scanf("%d", &k);
		while(k --> 0) {
			scanf("%d", &v);
			adjU[u].push_back(v);
		}
	}
	int nmatches = 0;
	for (int u = 1; u <= m; u++) {
		int v;
		scanf("%d", &v);
		if (v == 0) continue;
		nmatches++;
		pairU[u] = v;
		pairV[v] = u;
	}
	minimumcover();
	printf("%d\n", nmatches);
	printf("%u", coverU.size());
	for(int u : coverU) printf(" %d", u);
	printf("\n");
	printf("%u", coverV.size());
	for(int v : coverV) printf(" %d", v);
	printf("\n");
	return 0;
}