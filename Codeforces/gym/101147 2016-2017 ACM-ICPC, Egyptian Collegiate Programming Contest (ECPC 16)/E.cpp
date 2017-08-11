#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

typedef long long ll;
ll d[MAXN], dist[MAXN];
vector<int> adjList[MAXN];

int main() {
	freopen("jumping.in", "r", stdin);
	
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=1; i<=N; i++) {
			adjList[i].clear();
		}
		for(int i=1; i<=N; i++) {
			scanf("%I64d", &d[i]);
			dist[i] = -1;
			if (i+d[i] <= N) adjList[i+d[i]].push_back(i);
			if (i-d[i] > 0) adjList[i-d[i]].push_back(i);
		}
		dist[N] = 0;
		queue<int> q;
		q.push(N);
		while(!q.empty()) {
			int u = q.front(), v;
			q.pop();
			for(int i=0; i<(int)adjList[u].size(); i++) {
				v = adjList[u][i];
				if (dist[v] < 0) {
					dist[v] = dist[u] + 1LL;
					q.push(v);
				}
			}
		}
		for(int i=1; i<=N; i++) {
			printf("%I64d\n", dist[i]);
		}
	}
	
	fclose(stdin); 
	return 0;
}