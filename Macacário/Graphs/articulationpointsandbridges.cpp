#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAXN 1009
#define UNVISITED -1

int num[MAXN], N, low[MAXN], parent[MAXN], counter, rootChildren, articulationVertex[MAXN], root;
vector<int> adjList[MAXN];

void tarjan(int u) {
	low[u] = num[u] = counter++;
	for (int j = 0, v; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (num[v] == UNVISITED) {
			parent[v] = u;
			if (u == root) rootChildren++;
			tarjan(v);
			if (low[v] >= num[u]) articulationVertex[u] = true;
			if (low[v] > num[u]) printf(" Edge (%d, %d) is a bridge\n", u, v);
			low[u] = min(low[u], low[v]);
		}
		else if (v != parent[u])
			low[u] = min(low[u], num[v]);
	}
}

int main() {
	counter = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&low, 0, sizeof low);
	memset(&parent, 0, sizeof parent);
	memset(&articulationVertex, 0, sizeof articulationVertex);
	printf("Bridges:\n");
	for (int i = 0; i < N; i++)
		if (num[i] == UNVISITED) {
			root = i; rootChildren = 0; tarjan(i);
			articulationVertex[root] = (rootChildren > 1);
		} // special case
	printf("Articulation Points:\n");
	for (int i = 0; i < N; i++)
		if (articulationVertex[i])
			printf(" Vertex %d\n", i);
	return 0;
}
