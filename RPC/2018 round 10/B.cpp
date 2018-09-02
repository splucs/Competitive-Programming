#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define MAXN 509
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define pb push_back
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x);
typedef pair<int, int> ii;

int d[MAXN][MAXN];

int main() {
	int n, m, x, y;
	while(scanf("%d %d %d %d", &n, &m, &x, &y) != EOF) {
		mset(d, INF);
		FOR(j, m) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			d[u][v] = min(d[u][v], w);
			d[v][u] = min(d[v][u], w);
		}
		int s, t;
		scanf("%d %d", &s, &t);
		FOR1(k, n) FOR1(i, n) FOR1(j, n) {
			d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
		}
		printf("%.2f\n", d[s][t]*1.0/(x+y));
	}
	return 0;
}