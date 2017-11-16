#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

vector<int> adj[MAXN];
bool leaf[MAXN];

int main() {
	int N, u, v;
	scanf("%d", &N);
	for(int i=0; i<N-1; i++){
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	queue<int> q;
	for(u=1; u<=N; u++){
		if (adj[u].size() == 1u) q.push(u);
	}
	memset(&leaf, false, sizeof leaf);
	while(!q.empty()) {
		u = q.front();
		q.pop();
		if (leaf[u] || adj[u].size() > 2u) continue;
		leaf[u] = true;
		for(int i=0; i<(int)adj[u].size(); i++){
			v = adj[u][i];
			if (!leaf[v]) q.push(v);
		}
	}
	bool possible = true;
	int cnt;
	for(int u=1; u<=N; u++) {
		if (!leaf[u]) {
			cnt = 0;
			for(int i=0; i<(int)adj[u].size(); i++){
				v = adj[u][i];
				if (!leaf[v]) cnt++;
			}
			if (cnt > 2) possible = false;
		}
	}
	if (possible) printf("YES\n");
	else printf("NO\n");
	return 0;
}