#include <bits/stdc++.h>
using namespace std;
#define MAXN ((1<<20)+109)
#define ALFA 27

vector<int> adjList[MAXN];
int nxt[MAXN][ALFA], dist[MAXN];
int sz = 0, tab[MAXN], par[MAXN], N, M;

int insert(int u, const char *s) {
	if (!s[0]) {
		if (tab[u] == 0) tab[u] = u;
		return u;
	}
	if (nxt[u][s[0]-'a'] == 0) {
		nxt[u][s[0]-'a'] = ++sz;
		par[sz] = u;
	}
	int v = insert(nxt[u][s[0]-'a'], s+1);
	if (tab[u] == 0) {
		tab[u] = v;
	}
	return v;
}

int search(int u, const char *s) {
	if (!s[0]) {
		//printf("dist[%d] = %d\n", u, dist[u]);
		return dist[u];
	}
	if (nxt[u][s[0]-'a'] == 0) {
		return dist[u] + strlen(s);
	}
	return search(nxt[u][s[0]-'a'], s+1);
}

char buffer[MAXN];

int main() {
	sz = 0;
	int root = ++sz;
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++) {
		scanf(" %s", buffer);
		insert(root, buffer);
	}
	
	tab[root] = 0;
	par[root] = 0;
	for(int u=1; u<=sz; u++) {
		dist[u] = -1;
		for(int i=0; i<ALFA; i++) {
			if (nxt[u][i] != 0) adjList[u].push_back(nxt[u][i]);
		}
		if (par[u] != 0) adjList[u].push_back(par[u]);
		if (tab[u] != 0) adjList[u].push_back(tab[u]);
	}
	
	dist[root] = 0;
	queue<int> q;
	q.push(root);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i=0; i<(int)adjList[u].size(); i++) {
			int v = adjList[u][i];
			if (dist[v] < 0) {
				dist[v] = 1 + dist[u];
				q.push(v);
			}
		}
	}
	
	for(int i=0; i<M; i++) {
		scanf(" %s", buffer);
		printf("%d\n", search(root, buffer));
	}
	
	return 0;
}