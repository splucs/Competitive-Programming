#include <vector>
using namespace std;
#define MAXN 100009

int par[MAXN], size[MAXN];
vector<int> adjList[MAXN];
int root, N, up[MAXN], fson[MAXN];
vector<int> chain[MAXN];
int nchs, nchain[MAXN], id[MAXN], depth[MAXN];

int sizedfs(int u, int p) {
	size[u] = 1; fson[u] = -1; par[u] = p;
	int msz = 0;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v == p) continue;
		size[u] += sizedfs(v, u);
		if (size[v] > msz) {
			fson[u] = v; msz = size[v];
		}
	}
	return size[u];
}

void builddfs(int u, int ch, int h) {
	nchain[u] = ch; id[u] = chain[ch].size();
	chain[ch].push_back(u);
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v == par[u]) continue;
		if (v == fson[u]) builddfs(v, ch, h+1);
		else {
			up[nchs] = u; depth[nchs] = h;
			chain[nchs].clear();
			builddfs(v, nchs++, h+1);
		}
	}
}

void heavylightdecomposition(int _root) {
	root = _root;
	sizedfs(root, -1);
	nchs = 0; chain[0].clear();
	up[nchs] = -1; depth[nchs] = 0;
	builddfs(root, nchs++, 1);
}

int LCA(int u, int v) {
	int cu = nchain[u], cv = nchain[v];
	while(cu != cv) {
		if (depth[cu] > depth[cv]) u = up[cu];
		else v = up[cv];
		cu = nchain[u]; cv = nchain[v];
	}
	if (id[u] < id[v]) return u;
	else return v;
}

/*
 * SPOJ LCA
 */

#include <cstdio>
int main() {
	int T, Q, m, u, v;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo<=T; caseNo++) {
		scanf("%d", &N);
		for(u=1; u<=N; u++) {
			scanf("%d", &m);
			adjList[u].clear();
			while(m-->0) {
				scanf("%d", &v);
				adjList[u].push_back(v);
			}
		}
		heavylightdecomposition(1);
		printf("Case %d:\n", caseNo);
		scanf("%d", &Q);
		for(int q=0; q<Q; q++) {
			scanf("%d %d", &u, &v);
			printf("%d\n", LCA(u, v));
		}
	}
	return 0;
}