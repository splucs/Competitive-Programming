#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define UNVISITED -1
#define EXPLORED -2
#define VISITED -3

map<int, map<int, map<int, int> > > id3d;
map<int, map<int, int> > id2d, edges2d, edges3d;
int K, E2d = 0, E3d = 0, V2d = 0, V3d = 0;
bool cycle3d = false, cycle2d = false;
vector<int> adj3[MAXN], adj2[MAXN];
int vis3[MAXN], vis2[MAXN];

int insertV3(int x, int y, int z) {
	if (!id3d.count(x) || !id3d[x].count(y) || !id3d[x][y].count(z)) id3d[x][y][z] = ++V3d;
	return id3d[x][y][z];
}

void insertE3(int i, int j) {
	if (i == j) return;
	if (!edges3d.count(i) || !edges3d[i].count(j)){
		edges3d[i][j] = edges3d[j][i] = ++E3d;
		adj3[i].push_back(j);
		adj3[j].push_back(i);
	}
}

int insertV2(int x, int y) {
	if (!id2d.count(x) || !id2d[x].count(y)) id2d[x][y] = ++V2d;
	return id2d[x][y];
}

void insertE2(int i, int j) {
	if (i == j) return;
	if (!edges2d.count(i) || !edges2d[i].count(j)){
		edges2d[i][j] = edges2d[j][i] = ++E2d;
		adj2[i].push_back(j);
		adj2[j].push_back(i);
	}
}

void dfs3(int u, int par) {
	vis3[u] = EXPLORED;
	for (int j = 0, v; j < (int)adj3[u].size(); j++) {
		v = adj3[u][j];
		if (v == par) continue;
		if (vis3[v] == UNVISITED) {
			dfs3(v, u);
		}
		else if (vis3[v] == EXPLORED) {
			cycle3d = true;
		}
	}
	vis3[u] = VISITED;
}

void dfs2(int u, int par) {
	vis2[u] = EXPLORED;
	for (int j = 0, v; j < (int)adj2[u].size(); j++) {
		v = adj2[u][j];
		if (v == par) continue;
		if (vis2[v] == UNVISITED) {
			dfs2(v, u);
		}
		else if (vis2[v] == EXPLORED) {
			cycle2d = true;
		}
	}
	vis2[u] = VISITED;
}

int main()
{
	int x, y, z, xl, yl, zl, u, v;
	E2d = 0, E3d = 0, V2d = 0, V3d = 0;
	scanf("%d", &K);
	
	while(K--) {
		scanf("%d %d %d %d %d %d", &x, &y, &z, &xl, &yl, &zl);
		
		u = insertV3(x, y, z);
		v = insertV3(xl, yl, zl);
		vis3[u] = vis3[v] = UNVISITED;
		if (u != v) {
			insertE3(u, v);
		}
		
		u = insertV2(x, y);
		v = insertV2(xl, yl);
		vis2[u] = vis2[v] = UNVISITED;
		if (u != v) {
			insertE2(u, v);
		}
	}
	
	for(int i=1; i<=V3d; i++) if(vis3[i] == UNVISITED) dfs3(i, -1);
	if (cycle3d) printf("True closed chains\n");
	else printf("No true closed chains\n");
	
	for(int i=1; i<=V2d; i++) if(vis2[i] == UNVISITED) dfs2(i, -1);
	if (cycle2d) printf("Floor closed chains\n");
	else printf("No floor closed chains\n");
	return 0;
}