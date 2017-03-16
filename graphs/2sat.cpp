#include <cstdio>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAXN 400009
#define UNVISITED -1
#define EXPLORED -2
#define VISITED -3

int num[MAXN], vis[MAXN], component[MAXN], low[MAXN];
int value[MAXN], N, M, counter, root, numSCC;
stack<int> S;
vector<int> adjList[MAXN], toposort, C[MAXN];
set<int> adjComp[MAXN];

void dfs(int u) {
	low[u] = num[u] = counter++;
	S.push(u);
	vis[u] = 1;
	int v;
	for (int j = 0; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (num[v] == UNVISITED) dfs(v);
		if (vis[v]) low[u] = min(low[u], low[v]);
	}
	if (low[u] == num[u]) {
		while (true) {
			v = S.top(); S.pop(); vis[v] = 0;
			component[v] = numSCC;
			if (u == v) break;
		}
		numSCC++;
	}
}

void tarjan() {
	counter = numSCC = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&vis, 0, sizeof vis);
	memset(&low, 0, sizeof low);
	for (int i = 0; i < N; i++) {
		if (num[i] == UNVISITED)
			dfs(i);
	}
}

void ts(int u) {
	vis[u] = VISITED;
	set<int>::iterator it;
	for (it = adjComp[u].begin(); it != adjComp[u].end(); it++) {
		if (vis[*it] == UNVISITED) dfs(*it);
	}
	toposort.push_back(u);
}

bool ffill(int u, int k) {
	value[u] = k;
	int v = (u >= N / 2 ? u - N / 2 : u + N / 2);
	if (value[v] == value[u]) return false;
	if (value[v] == -1 && !ffill(v, 1 - k)) return false;
	for (int i = 0; i<(int)adjList[u].size(); i++) {
		v = adjList[u][i];
		if (value[v] == 0 && k == 1) return false;
		if (value[v] == -1 && (component[u] == component[v]
			|| k == 1) && !ffill(v, k)) return false;
	}
	return true;
}

bool twosat() {
	tarjan();
	for (int i = 0; i<N / 2; i++) {
		C[i].clear(); adjComp[i].clear();
		if (component[i] == component[i + N / 2]) return false;
	}
	for (int u = 0, v; u<N; u++) {
		C[component[u]].push_back(u);
		for (int i = 0; i<(int)adjList[u].size(); i++) {
			v = adjList[u][i];
			if (component[u] != component[v])
				adjComp[component[u]].insert(component[v]);
		}
	}
	memset(&vis, UNVISITED, sizeof vis);
	toposort.clear();
	for (int i = 0; i<numSCC; i++) {
		if (vis[i] == UNVISITED) ts(i);
	}
	memset(&value, -1, sizeof value);
	for (int i = 0, c, u; i<(int)toposort.size(); i++) {
		c = toposort[i];
		for (int j = 0; j<(int)C[c].size(); j++) {
			u = C[c][j];
			if (value[u] == -1 && !ffill(u, 1))
				return false;
		}
	}
	return true;
}