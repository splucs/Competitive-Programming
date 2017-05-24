#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

int adj[MAXN], deg[MAXN], par[MAXN];
typedef pair<int, int> ii;

int main()
{
	int N;
	while(scanf("%d", &N)!=EOF) {
		memset(&deg, 0, sizeof deg);
		for(int i=1; i<=N; i++) {
			scanf("%d", &adj[i]);
			deg[adj[i]]++;
		}
		set<ii> pq;
		for(int i=1; i<=N; i++) {
			pq.insert(ii(deg[i], i));
		}
		bool possible = true;
		while(!pq.empty()){
			int u = pq.begin()->second;
			int v = adj[u];
			int w = adj[v];
			if (!pq.count(ii(deg[v], v))){
				possible = false;
				break;
			}
			par[u] = v;
			par[v] = u;
			pq.erase(ii(deg[u], u));
			pq.erase(ii(deg[v], v));
			deg[v]--;
			deg[w]--;
			if (pq.count(ii(deg[w]+1, w))){
				pq.erase(ii(deg[w]+1, w));
				pq.insert(ii(deg[w], w));
			}
		}
		if (!possible) printf("IMPOSSIBLE\n");
		else {
			for(int i=1; i<=N; i++) {
				printf("%d", par[i]);
				if (i < N) printf(" ");
			}
			printf("\n");
		}
	}
	return 0;
}