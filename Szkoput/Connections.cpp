#include <vector>
#include <map>
using namespace std;
#define MAXN 109
typedef pair<int, int> ii;

/*
 * k-Sijkstra O(nklogn)
 */

vector<ii> adjList[MAXN];

void dijkstra(int s, int k, vector<int> kdist[]) {
	map<ii, int> cnt;
	cnt[ii(0, s)]++;
	while(!cnt.empty()) {
		pair<ii, int> cur = *cnt.begin();
		int u = cur.first.second;
		int wu = cur.first.first;
		int am = cur.second;
		cnt.erase(cnt.begin());
		if (am == 0 || kdist[u].size() >= k) continue;
		for(int i = 0; i < am; i++) {
			if (wu == 0 || kdist[u].size() >= k) break;
			kdist[u].push_back(wu);
		}
		for(int i = 0; i < (int)adjList[u].size(); i++) {
			int v = adjList[u][i].second;
			int w = adjList[u][i].first;
			int &cv = cnt[ii(w + wu, v)];
			cv = min(cv + am, k);
		}
	}
}

/*
 * Szkoput Connections
 */

#include <cstdio>
vector<int> ans[MAXN][MAXN];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	while(m --> 0) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		adjList[u].push_back(ii(w, v));
	}
	for(int s = 1; s <= n; s++)
		dijkstra(s, 100, ans[s]);
	int q;
	scanf("%d\n", &q);
	while(q --> 0) {
		int s, t, k;
		scanf("%d %d %d", &s, &t, &k);
		if (k-1 >= ans[s][t].size()) printf("-1\n");
		else printf("%d\n", ans[s][t][k-1]);
	}
	return 0;
}