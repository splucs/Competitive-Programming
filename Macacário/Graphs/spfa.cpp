#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
#define MAXN 100009
#define INF 0x3f3f3f3f
typedef pair<int, int> ii;

/*
 * Shortest Path Faster Algorithm (SPFA) O(nm) worst case, O(n) average
 */

vector<ii> adjList[MAXN];
int dist[MAXN], vis[MAXN], N, M;
bool inq[MAXN];
 
int spfa(int s, int t) {
	for(int i=0; i<=N; i++) dist[i] = INF;
	memset(&inq, false, sizeof inq);
	memset(&vis, 0, sizeof vis);
	queue<int> q;
	q.push(s);
	dist[s] = 0;
	inq[s] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (vis[u] > N) return -1;
		inq[u] = false;
		for (int i = 0; i < (int)adjList[u].size(); i++) {
			int v = adjList[u][i].second;
			int w = adjList[u][i].first;
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				if (!inq[v]) {
					vis[v]++; q.push(v);
					inq[v] = true;
				}
			}
		}
	}
	return dist[t];
}

/*
 * SPOJ EZDIJKST
 */

#include <cstdio>

int main() {
	int T;
	int u, v, w, s, t;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &N, &M);
		for(int i=1; i<=N; i++) adjList[i].clear();
		for(int i=0; i<M; i++) {
			scanf("%d %d %d", &u, &v, &w);
			adjList[u].push_back(ii(w, v));
		}
		scanf("%d %d", &s, &t);
		int ans = spfa(s, t);
		if (ans == INF) printf("NO\n");
		else printf("%d\n", ans);
	}
	return 0;
}