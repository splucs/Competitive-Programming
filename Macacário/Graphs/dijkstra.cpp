#include <iostream>
using namespace std;


/*
 * Dijkstra's Algorithm O(nlogn + m)
 */

#include <set>
#include <array>
#include <vector>
#define MAXN 100009
#define INF 0x3f3f3f3f
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<int, vi> ivi; 
vector<ii> adjList[MAXN];
array<int, MAXN> dist;


ivi dijkstra(int s, int t, int n) {
	dist.fill(INF);
	vi path;
	path.push_back(s);
	
	set<ii> pq;
	dist[s] = 0;
	pq.insert(ii(0, s));
	while(!pq.empty()) {
		int u{pq.begin()->second};
		pq.erase(pq.begin());
		for(ii item : adjList[u]){
			int w{item.first}, v{item.second};
			// v -> No destiono
			// w -> Valor aresta
			if (dist[v] > dist[u] + w) {
				pq.erase(ii(dist[v], v));
				dist[v] = dist[u] + w;
				pq.insert(ii(dist[v], v));
				path.push_back(v);
			}
		}
	}

	// Retorna o valor total do caminho e o caminho
	return ivi(dist[t], path);
}

/*
 * SPOJ EZDIJKST
 */



int n{5}, m{4};
 
int main() {
	int T;
	int u, v, w, s, t;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		for(int i=1; i<=n; i++) adjList[i].clear();
		for(int i=0; i<m; i++) {
			scanf("%d %d %d", &u, &v, &w);
			adjList[u].push_back(ii(w, v));
		}
		scanf("%d %d", &s, &t);
		ivi ans = dijkstra(s, t, n);
		if (ans.first == INF) printf("NO\n");
		else printf("%d\n", ans.first);
	}
	
	return 0;
}