#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
#define MAXN 1009

int N, M, K;
int dist[MAXN], C[MAXN], ans[MAXN];
vector<int> adjList[MAXN];

void bfs(int s){
	memset(&dist, -1, sizeof dist);
	queue<int> q;
	q.push(s);
	dist[s] = 0;
	int u, v;
	while(!q.empty()){
		u = q.front();
		q.pop();
		if (dist[u] == K && C[s] == C[u]) ans[C[s]]++;
		for(int i=0; i<(int)adjList[u].size(); i++){
			v = adjList[u][i];
			if (dist[v] < 0){
				dist[v] = 1 + dist[u];
				q.push(v);
			}
		}
	}
}

int main(){
	scanf("%d %d %d", &N, &M, &K);
	memset(&ans, 0, sizeof ans);
	for(int i=1; i<=N; i++){
		scanf("%d", &C[i]);
	}
	for(int u=2, v; u<=N; u++){
		scanf("%d", &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	for(int i=1; i<=N; i++){
		bfs(i);
	}
	for(int i=1; i<=M; i++){
		if (i>1) printf(" ");
		printf("%d", ans[i]/2);
	}
	printf("\n");
	return 0;
}