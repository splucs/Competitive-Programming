#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define MAXN 100009

vector<int> adjList[MAXN], csons[MAXN];
int label[MAXN], cpar[MAXN], size[MAXN], N;

int sizedfs(int u, int p, int & nn) {
	size[u] = 1;
	nn++;
	for (int i = 0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v != p && label[v] < 0)
			size[u] += sizedfs(v, u, nn);
	}
	return size[u];
}
int centroiddfs(int u, int p, int nn) {
	for (int i = 0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v != p && label[v] < 0 && size[v] > nn / 2)
			return centroiddfs(v, u, nn);
	}
	return u;
}
int decomposedfs(int root, int p) {
	int nn = 0;
	sizedfs(root, root, nn);
	int u = centroiddfs(root, root, nn);
	if (p == -1) p = u;
	cpar[u] = p;
	csons[p].push_back(u);
	label[u] = label[p] + 1;
	size[u] = 1;
	for (int i = 0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		if (v != p && label[v] < 0) {
			size[u] += size[decomposedfs(v, u)];
		}
	}
	return u;
}
int centroiddecomposition() {
	memset(&label, -1, sizeof label);
	return decomposedfs(1, -1);
}