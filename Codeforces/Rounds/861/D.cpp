#include <bits/stdc++.h>
using namespace std;
#define MAXS 70001
#define MAXN (MAXS*50)

int adjList[MAXN][10];
char car[MAXN];
int sz, root, par[MAXN], end[MAXN], dep[MAXN];

int newnode(char c, int p, int id) {
	par[sz] = p;
	dep[sz] = p >= 0 ? dep[p] + 1 : 1;
	for(int k=0; k<10; k++) adjList[sz][k] = -1;
	car[sz] = c;
	end[sz] = id;
	sz++;
	return sz-1;
}

void insert(char* str, int id) {
	int n = root;
	while(str[0]) {
		if (adjList[n][str[0] - '0'] < 0) adjList[n][str[0] - '0'] = newnode(str[0], n, id);
		n = adjList[n][str[0] - '0'];
		if (end[n] != id) end[n] = -1;
		str++;
	}
}

int ans[MAXS];

void dfs(int u) {
	for(int i=0; i<10; i++) {
		int v = adjList[u][i];
		if (v == -1) continue;
		dfs(v);
	}
	if (end[u] != -1) {
		int i = end[u];
		if (ans[i] == -1) ans[i] = u;
		else if (dep[ans[i]] > dep[u]) ans[i] = u;
	}
}

int N;
char buffer[15];

int main() {
	sz = 0;
	root = newnode(0, -1, -1);
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		ans[i] = -1;
		scanf(" %s", buffer);
		for(int j=0; j<9; j++) insert(buffer + j, i);
	}
	dfs(root);
	for(int i=0; i<N; i++) {
		int u = ans[i];
		buffer[dep[u]-1] = 0;
		while(u != root) {
			buffer[dep[u]-2] = car[u];
			u = par[u];
		}
		printf("%s\n", buffer);
	}
	return 0;
}