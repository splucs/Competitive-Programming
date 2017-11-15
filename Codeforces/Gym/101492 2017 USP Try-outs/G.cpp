#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define INF 1000000009
#define FOR(x,n) for(int x = 0; x < n; x++)
#define UNVISITED -1
typedef pair<int,int> ii;

int num[MAXN], N, low[MAXN], parent[MAXN], counter, rootChildren, root;
vector<int> adjList[MAXN];
set<int> vizinhos[MAXN];
set<ii> removed;

void tarjan(int u) {
	low[u] = num[u] = counter++;
	for (int j = 0, v; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (num[v] == UNVISITED) {
			parent[v] = u;
			if (u == root) rootChildren++;
			tarjan(v);
			if (low[v] > num[u]) removed.insert(ii(min(u,v), max(u,v)));
			low[u] = min(low[u], low[v]);
		}
		else if (v != parent[u])
			low[u] = min(low[u], num[v]);
	}
}

int main(){
	counter = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&low, 0, sizeof low);
	memset(&parent, 0, sizeof parent);
	int m, a, b;
	
	scanf("%d %d", &N, &m);
	
	while(m--) {
		scanf("%d %d", &a, &b);
		a--; b--;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}
	
	for (int i = 0; i < N; i++)
		if (num[i] == UNVISITED) {
			root = i; rootChildren = 0; tarjan(i);
		}
	
	int ans = min(N, 2);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < adjList[i].size(); j++) {
			if (removed.find(ii(i, adjList[i][j]) )!= removed.end() || removed.find(ii(adjList[i][j], i)) != removed.end()) continue;
			vizinhos[i].insert(adjList[i][j]);
		}
	}
	
	for (int i = 0; i < N; i++) {
		while (!vizinhos[i].empty()) {
			set<int>::iterator it = vizinhos[i].begin();
			
			vector<int> intersec;
			set<int>::iterator pi = vizinhos[i].begin();
			set<int>::iterator pj = vizinhos[*it].begin();
			while (pi != vizinhos[i].end() && pj != vizinhos[*it].end()) {
				if ((*pi) == (*pj)) {
					intersec.push_back(*pi); pi++; pj++;
				} else if ((*pi) < (*pj)) pi++;
				else pj++;
			}
			intersec.push_back(i);
			intersec.push_back(*it);
			ans = max(ans, (int)intersec.size());
			
			for (int a = 0; a < intersec.size(); a++) {
				for (int b = a+1; b < intersec.size(); b++) {
					vizinhos[intersec[a]].erase(intersec[b]);
					vizinhos[intersec[b]].erase(intersec[a]);
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}