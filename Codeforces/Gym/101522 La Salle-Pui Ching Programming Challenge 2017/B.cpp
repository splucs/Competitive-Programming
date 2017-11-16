#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009

int N, dist[MAXN];
vector<int> adjList[MAXN];

void farthest(int s, int & t, int & ans) {
	queue<int> q;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	q.push(s);
	int u, v;
	while(!q.empty()) {
		u = q.front(); q.pop();
		for(int i=0; i<(int)adjList[u].size(); i++) {
			v = adjList[u][i];
			if (dist[v] < 0) {
				dist[v] = 1 + dist[u];
				q.push(v);
				ans = dist[v];
				t = v;
			}
		}
	}
}

int main() {
	
	scanf("%d", &N);
	for(int i=1, u, v; i<N; i++) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	int t, ans;
	farthest(1, t, ans);
	farthest(t, t, ans);
	int cnt = 0;
	while(ans > 1) {
		if ((ans & 1) != 0) ans++;
		ans >>= 1;
		cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}