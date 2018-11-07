#include <cstdio>
#include <vector>
using namespace std;
#define MAXN 1009
#define UNVISITED -1
#define EXPLORED -2
#define VISITED -3

int vis[MAXN], parent[MAXN];
vector<int> adjList[MAXN];

void dfs(int u) { // DFS for checking graph edge properties
	vis[u] = EXPLORED;
	for (int j = 0, v; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (vis[v] == UNVISITED) { // EXPLORED->UNVISITED
			printf(" Tree Edge (%d, %d)\n", u, v);
			parent[v] = u; // parent of this children is me
			dfs(v);
		}
		else if (vis[v] == EXPLORED) { // EXPLORED->EXPLORED
			printf(" Back Edge (%d, %d) (Cycle)\n", u, v);
		}
		else if (vis[v] == VISITED) // EXPLORED->VISITED
			printf(" Forward/Cross Edge (%d, %d)\n", u, v);
	}
	vis[u] = VISITED; // after recursion, color u as VISITED (DONE)
}