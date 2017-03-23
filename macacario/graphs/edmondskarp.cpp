#include <vector>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF (1<<30)
#define MAXN 109
using namespace std;

vector<int> adjList[MAXN];
int p[MAXN], cap[MAXN][MAXN], dist[MAXN], N, M;

int augment(int v, int minEdge, int s) {
	if (v == s) return minEdge;
	else if (p[v] != -1) {
		int f = augment(p[v], min(minEdge, cap[p[v]][v]), s);
		cap[p[v]][v] -= f;
		cap[v][p[v]] += f;
		return f;
	}
	return 0;
}

bool bfs(int s, int t){
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	memset(&p, -1, sizeof p);
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (u == t) break;
		for(int i = 0; i<(int)adjList[u].size(); i++){
			v = adjList[u][i];
			if (dist[v] < 0 && cap[u][v] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
				p[v] = u;
			}
		}
	}
	return dist[t] >= 0;
}

//O(VE^2)
int edmondskarp(int s, int t){
	int result = 0;
	while (bfs(s, t)) {
		result += augment(t, INF, s);
	}
	return result;
}

int main(){
	N = MAXN;
	scanf("%d", &M);
	char cu, cv;
	int u, v, f;
	memset(&cap, 0, sizeof cap);
	for(int i=0; i<M; i++){
		scanf(" %c %c %d", &cu, &cv, &f);
		if(cu >='A' && cu <= 'Z') u = cu-'A';
		else u = cu-'a'+'Z'-'A'+1;
		if(cv >='A' && cv <= 'Z') v = cv-'A';
		else v = cv-'a'+'Z'-'A'+1;
		if (cap[u][v]==0 && cap[v][u]==0){
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}
		cap[u][v] += f;
	}
	printf("%d\n", edmondskarp(0, 'Z'-'A'));
	return 0;
}