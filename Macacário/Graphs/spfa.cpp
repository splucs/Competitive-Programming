/*
 * Solução do problema http://www.spoj.com/submit/EZDIJKST/
 */
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
#define MAXN 100009
#define INF (1<<30)
 
typedef pair<int, int> ii;
vector<ii> adjList[MAXN];
int dist[MAXN], n, m;
bool inq[MAXN];
 
int spfa(int s, int t){
	for(int i=0; i<=n; i++) dist[i] = INF;
	memset(&inq, false, sizeof inq);
	queue<int> q;
	q.push(s);
	dist[s] = 0;
	inq[s] = true;
	while (!q.empty()){
		int u = q.front(); q.pop();
		inq[u] = false;
		for (int i = 0; i < (int)adjList[u].size(); i++) {
			int v = adjList[u][i].second;
			int w = adjList[u][i].first;
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				if (!inq[v]) {
					q.push(v);
					inq[v] = true;
				}
			}
		}
	}
	return dist[t];
}
 
int main(){
	int T;
	int u, v, w, s, t;
	scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &m);
		for(int i=1; i<=n; i++) adjList[i].clear();
		for(int i=0; i<m; i++){
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