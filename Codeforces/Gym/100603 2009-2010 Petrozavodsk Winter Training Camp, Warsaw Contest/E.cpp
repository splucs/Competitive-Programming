#include <bits/stdc++.h>
using namespace std;
#define MAXN 409
#define ALFA 29
#define INF (1<<30)

int pos[MAXN][MAXN][ALFA], N, M, dist[MAXN*MAXN*ALFA], par[MAXN*MAXN*ALFA];
int nj[MAXN*MAXN*ALFA], ni[MAXN*MAXN*ALFA], car[MAXN*MAXN*ALFA];
typedef pair<int, int> ii;
vector<ii> adjList[MAXN], revAdj[MAXN];
int tab[MAXN][MAXN], s[MAXN];

int main() {
	scanf("%d %d", &N, &M);
	int u, v;
	char w;
	memset(&tab, -1, sizeof tab);
	for(int j=0; j<M; j++) {
		scanf("%d %d %c", &u, &v, &w);
		adjList[u].push_back(ii(w - 'a' + 1, v));
		revAdj[v].push_back(ii(w - 'a' + 1, u));
		tab[u][v] = w - 'a' + 1;
	}
	queue<int> q, q1;
	for(int i=1, k=0; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			for(w=0; w<ALFA; w++) {
				pos[i][j][w] = ++k;
				ni[k] = i;
				nj[k] = j;
				car[k] = w;
				dist[k] = INF;
				if (i == j && w == 0) {
					q.push(k);
					dist[k] = 0;
					par[k] = -1;
				}
				else if (tab[i][j] >= 0 && w == 0) {
					q1.push(k);
					dist[k] = 1;
					par[k] = -1;
				}
			}
		}
	}
	while(!q1.empty()) {
		q.push(q1.front());
		q1.pop();
	}
	while(!q.empty()) {
		u = q.front();
		q.pop();
		int nu = ni[u];
		int nv = nj[u];
		if (car[u] > 0) {
			for(int it = 0; it<(int)adjList[nv].size(); it++) {
				int mv = adjList[nv][it].second;
				if (adjList[nv][it].first != car[u]) continue;
				v = pos[nu][mv][0];
				if (dist[v] < dist[u] + 1) {
					dist[v] = dist[u] + 1;
					par[v] = u;
					q.push(v);
				}
			}
		}
		else {
			for(int it = 0; it<(int)revAdj[nu].size(); it++) {
				int mu = revAdj[nu][it].second;
				v = pos[mu][nv][revAdj[nu][it]];
				if (dist[v] < dist[u] + 1) {
					dist[v] = dist[u] + 1;
					par[v] = u;
					q.push(v);
				}
			}
		}
	}
	int D;
	scanf("%d", &D);
	for(int i=1; i<=D; i++) {
		scanf("%d", &s[i]);
		if (i == 1) continue;
		u = pos[s[i-1]][s[i]][0];
		if (dist[u] == INF) {
			printf("-1\n");
			continue;
		}
		printf("%d ", dist[u]);
		stack<char> st;
		while(true) {
			if (par[u] == -1) {
				if (ni[u] != nj[u]) printf("%c", tab[ni[u]][nj[u]]);
				break;
			}
			w = car[par[u]] - 1 + 'a';
			printf("%c", w);
			st.push(w);
			u = par[par[u]];
		}
		while(st.empty()) {
			printf("%c", st.top());
			st.pop();
		}
		printf("\n");
	}
	return 0;
}