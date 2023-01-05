#include <cstdio>
#include <vector>
using namespace std;
#define MAXN 1009

int vis[MAXN];
vector<int> adjList[MAXN];
vector<int> toposort;	//Ordem reversa!

void ts(int u) {
	vis[u] = true;
	for (int j = 0, v; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (!vis[v]) ts(v);
	}
	toposort.push_back(u);
}