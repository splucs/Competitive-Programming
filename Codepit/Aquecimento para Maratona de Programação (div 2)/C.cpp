#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1<<30)

int N, S, Q, M;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
vector<int> adjList[MAXN];
int dist[MAXN];
iii val[MAXN];

int main() {
	int p, m, t, u, v;
	while(scanf("%d %d %d %d", &N, &S, &Q, &M) != EOF) {
		for(int i=1; i<=N; i++) {
			dist[i] = INF;
			val[i] = iii(ii(0, 0), 0);
			adjList[i].clear();
		}
		queue<int> q;
		for(int i=1; i<=S; i++) {
			scanf("%d %d %d", &p, &m, &t);
			if (dist[p] == INF) {
				dist[p] = 0;
				q.push(p);
			}
			val[p] = max(val[p], iii(ii(m, t), i));
		}
		for(int j=0; j<M; j++) {
			scanf("%d %d", &u, &v);
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}
		while(!q.empty()) {
			u = q.front();
			q.pop();
			for(int i=0; i<(int)adjList[u].size(); i++) {
				v = adjList[u][i];
				if (dist[v] > dist[u] + 1) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
				if (dist[v] == dist[u] + 1) {
					val[v] = max(val[v], val[u]);
				}
			}
		}
		while(Q-->0) {
			scanf("%d", &u);
			if (val[u].second == 0) printf("Noic\n");
			else printf("%d\n", val[u].second);
		}
	}
	return 0;
}