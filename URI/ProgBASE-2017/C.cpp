#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define INF (1LL<<60)

long long row[MAXN], dist[MAXN][MAXN];

int main() {
	int N, M;
	while(scanf("%d %d", &N, &M), N>0 || M>0) {
		for(int i=1; i<=N; i++) {
			for(int j=1; j<=N; j++) {
				dist[i][j] = INF;
			}
			dist[i][i] = 0;
		}
		int u, v;
		long long w;
		while(M-->0) {
			scanf("%d %d %lld", &u, &v, &w);
			dist[u][v] = min(dist[u][v], w);
			dist[v][u] = min(dist[v][u], w);
		}
		for(int k=1; k<=N; k++) {
			for(int i=1; i<=N; i++) {
				for(int j=1; j<=N; j++) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
		vector<int> ans;
		long long mind = (1LL<<60);
		for(int i=1; i<=N; i++) {
			row[i] = 0;
			for(int j=1; j<=N; j++) {
				row[i] += dist[i][j];
			}
			if (mind > row[i]) ans.clear(), mind = row[i];
			if (mind == row[i]) ans.push_back(i);
		}
		for(int i=0; i<(int)ans.size(); i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	return 0;
}