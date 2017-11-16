#include <vector>
using namespace std;
#define MAXN 300009

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

void builddfs(int u, int ch, int h){
	nchain[u] = ch; id[u] = chain[ch].size();
	chain[ch].push_back(u);
	for(int i=0; i<(int)adjList[u].size(); i++){
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
#include <cstdio>

void heavylightdecomposition(int _root) {
	root = _root;
	sizedfs(root, -1);
	nchs = 0; chain[0].clear();
	up[nchs] = -1; depth[nchs] = 0;
	builddfs(root, nchs++, 1);
	
	/*for(int c=0; c<nchs; c++) {
		printf("chain %d:", c);
		for(int i=0; i<(int)chain[c].size(); i++) {
			printf(" %d", chain[c][i]);
		}
		printf("\n");
	}*/
}

#include <map>
#include <string>
#include <iostream>
map<string, map<int, string> > hld[MAXN];
map<string, string> kv[MAXN];

char buffer[30];

int query(int u, string str) {
	int c = nchain[u];
	map<int, string>::iterator it = hld[c][str].lower_bound(N-id[u]);
	//printf("looking at chain %d for %s starting at pos %d\n", c, str.c_str(), id[u]);
	while(it == hld[c][str].end()) {
		u = up[c];
		if (u >= 0) {
			c = nchain[u];
			it = hld[c][str].lower_bound(N-id[u]);
		}
		else break;
		//printf("looking at chain %d for %s starting at pos %d\n", c, str.c_str(), id[u]);
	}
	if (u < 0) return -1;
	return chain[c][N-it->first]; 
}

int main(){
	int u, v, k, Q;
	scanf("%d", &N);
	for(v=1; v<=N; v++) {
		scanf("%d %d", &u, &k);
		adjList[u].push_back(v);
		for(int j=0; j<k; j++) {
			scanf("%s", buffer);
			int len = 0;
			while(buffer[len] != '=') len++;
			buffer[len] = 0;
			kv[v][buffer] = &buffer[len+1];
			//printf("node %d: %s-%s\n", u, buffer, &buffer[len+1]);
		}
	}
	heavylightdecomposition(1);
	for(int c=0; c<nchs; c++) {
		for(int i=0; i<(int)chain[c].size(); i++) {
			u = chain[c][i];
			for(map<string, string>::iterator it = kv[u].begin(); it != kv[u].end(); it++) {
				hld[c][it->first][N-i] = it->second;
			}
		}
	}
	scanf("%d", &Q);
	while(Q-->0) {
		scanf("%d %s", &u, buffer);
		v = query(u, buffer);
		if (v == -1) printf("N/A\n");
		else printf("%s\n", kv[v][buffer].c_str());
		fflush(stdout);
	}
	return 0;
}