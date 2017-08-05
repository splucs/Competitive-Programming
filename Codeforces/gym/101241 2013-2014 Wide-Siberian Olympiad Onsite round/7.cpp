#include <bits/stdc++.h>
using namespace std;
#define MAXN 50009
#define ALFA 70

char str[MAXN], carac[MAXN];
int adj[MAXN][ALFA], sz, gru=0;
const int root = 0;
bool end[MAXN], possible;
set<int> vis[MAXN];

inline int carac2id(char c){
	if (c >= 'a' && c <= 'z') return c - 'a';
	else if (c >= 'A' && c <= 'Z') return c - 'A' + 'z'-'a';
	else if (c >= '0' && c <= '9') return c - '0' + 'z'-'a' + 'Z'-'A';
	else return -1;
}

void dfs(int u, int v) {
	if (u == v) possible = true;
	if (u > v) swap(u, v);
	if (possible || vis[u].count(v)) return;
	//printf("dfs %d %d\n", u, v);
	gru++;
	if (gru > 2000000) possible = true;
	vis[u].insert(v);
	if (end[u]) dfs(root, v);
	if (end[v]) dfs(u, root);
	for(int j = 0; j<ALFA; j++) {
		if (adj[u][j] > 0 && adj[v][j] > 0) dfs(adj[u][j], adj[v][j]);
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int N;
	scanf("%d", &N);
	
	memset(&adj, 0, sizeof adj);
	memset(&end, false, sizeof end);
	sz = 1;
	carac[root] = '$';
	
	while(N-->0) {
		scanf(" %s", str);
		int cur = root;
		int len = strlen(str);
		for(int i=0; i<len; i++) {
			int ne = carac2id(str[i]);
			if (adj[cur][ne] == 0){
				carac[sz] = str[i];
				adj[cur][ne] = sz;
				//printf("node %d->%d(%d): %c\n", cur, sz, ne, str[i]);
				sz++;
			}
			cur = adj[cur][ne];
		}
		end[cur] = true;
	}
	
	possible = false;
	for(int i=0; i<sz && !possible; i++){
		if (!end[i]) continue;
		//printf("i=%d\n", i);
		for(int j = 0; j<ALFA; j++) {
			if (adj[i][j] > 0 && adj[root][j] > 0) dfs(adj[i][j], adj[root][j]);
		}
	}
	
	if (possible) printf("YES\n");
	else printf("NO\n");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}