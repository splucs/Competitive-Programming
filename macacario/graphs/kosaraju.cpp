#include <cstdio>
#include <vector>
#include <cstring>
#define MAXN 100009
using namespace std;

vector<int> adjList[MAXN], revAdjList[MAXN], toposort;
bool num[MAXN];
int component[MAXN], parent = 0, N, M, numSCC;

void revdfs(int u) {
	num[u] = true;
	for (int i = 0, v; i<(int)revAdjList[u].size(); i++) {
		v = revAdjList[u][i];
		if (!num[v]) revdfs(v);
	}
	toposort.push_back(u);
}

void dfs(int u) {
	num[u] = true;
	component[u] = parent;
	for (int i = 0, v; i<(int)adjList[u].size(); i++) {
		v = adjList[u][i];
		if (!num[v]) dfs(v);
	}
}

void kosaraju() {
	memset(&num, false, sizeof num);
	for (int i = 0; i<N; i++) {
		if (!num[i]) revdfs(i);
	}
	memset(&num, false, sizeof num);
	numSCC = 0;
	for (int i = N - 1; i >= 0; i--) {
		if (!num[toposort[i]]) {
			parent = toposort[i];
			dfs(toposort[i]);
			numSCC++;
		}
	}
}