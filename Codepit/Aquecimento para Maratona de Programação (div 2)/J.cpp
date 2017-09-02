#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int N, M;
vector<int> adjList[MAXN], keys[MAXN];
bool reach[MAXN], unlock[MAXN], vis[MAXN];

int main() {
	int u, v;
	while(scanf("%d %d", &N, &M)!=EOF) {
		for(int i=1; i<=N; i++) {
			adjList[i].clear();
			keys[i].clear();
		}
		while(M-->0) {
			scanf("%d %d", &u, &v);
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}
		int k;
		for(int i=2; i<=N; i++) {
			scanf("%d", &k);
			keys[k].push_back(i);
		}
		memset(&reach, false, sizeof reach);
		memset(&unlock, false, sizeof unlock);
		memset(&vis, false, sizeof vis);
		queue<int> q;
		q.push(1);
		vis[1] = unlock[1] = reach[1] = true;
		int ans = 1;
		while(!q.empty()) {
			u = q.front();
			q.pop();
			for(int i=0; i<(int)keys[u].size(); i++) {
				k = keys[u][i];
				unlock[k] = true;
				if (unlock[k] && reach[k] && !vis[k]) {
					q.push(k);
					vis[k] = true;
					ans++;
				}
			}
			for(int i=0; i<(int)adjList[u].size(); i++) {
				v = adjList[u][i];
				reach[v] = true;
				if (unlock[v] && reach[v] && !vis[v]) {
					q.push(v);
					vis[v] = true;
					ans++;
				}
			}
		}
		if (ans == N) printf("sim\n");
		else printf("nao\n");
	}
	return 0;
}