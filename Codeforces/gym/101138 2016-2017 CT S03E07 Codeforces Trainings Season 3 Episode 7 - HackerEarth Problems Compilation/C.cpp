#include <bits/stdc++.h>
using namespace std;
#define MAXN 209
#define MOD 1000000007LL

int N, M;
vector<int> adj[MAXN];
int adjMat[MAXN][MAXN];
typedef long long ll;
ll pascal[MAXN][4];

int main() {
	for(int n=0; n<MAXN; n++) {
		for(int k=0; k<4; k++) {
			if (n == k || k == 0) pascal[n][k] = 1;
			else if (n < k) pascal[n][k] = 0;
			else pascal[n][k] = (pascal[n-1][k] + pascal[n-1][k-1])%MOD;
		}
	}
	int u, v, w, a, b, c;
	scanf("%d %d", &N, &M);
	memset(&adjMat, 0, sizeof adjMat);
	for(int i=0; i<M; i++) {
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
		adjMat[u][v] = 1;
		adjMat[v][u] = 1;
	}
	ll ans = 0;
	for(u=1; u<=N; u++) {
		for(int it=0; it<(int)adj[u].size(); it++) {
			v = adj[u][it];
			a = b = c = 0;
			for(int i=0; i<(int)adj[u].size(); i++) {
				w = adj[u][i];
				if (w == v) continue;
				if (adjMat[v][w] == 0) a++;
				else b++;
			}
			for(int j=0; j<(int)adj[v].size(); j++) {
				w = adj[v][j];
				if (w == u) continue;
				if (adjMat[u][w] == 0) c++;
			}
			for(int k=0; k<4; k++) {
				ans += (((pascal[a][3-k]*pascal[b][k])%MOD)*pascal[b+c-k][2])%MOD;
				ans %= MOD;
			}
		}
	}
	printf("%I64d\n", ans);
	return 0;
}