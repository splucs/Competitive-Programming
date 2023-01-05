#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define MAXN 29
#define MAXM 29
#define INF 0x3f3f3f3f
typedef long long ll;

int n, m;
int pu[MAXN], pv[MAXN], cost[MAXN][MAXM];
int pairV[MAXN], way[MAXM], minv[MAXM];
bool used[MAXM];
void hungarian() {
	memset(&pairV, 0, sizeof pairV);
	for(int i = 1, j0 = 0; i <= n; i++) {
		printf("i = %d\n", i);
		pairV[0] = i;
		memset(&minv, INF, sizeof minv);
		memset(&used, false, sizeof used);
		do {
			used[j0] = true;
			int i0 = pairV[j0], delta = INF, j1;
			for(int j = 1; j <= m; j++) {
				if (used[j]) continue;
				int cur = cost[i0][j] - pu[i0] - pv[j];
				if (cur < minv[j])
					minv[j] = cur, way[j] = j0;
				if (minv[j] < delta)
					delta = minv[j], j1 = j;
			}
			for(int j = 0; j <= m; j++) {
				if (used[j])
					pu[pairV[j]] += delta, pv[j] -= delta;
				else minv[j] -= delta;
			}
			j0 = j1;
		} while(pairV[j0] != 0);
		do {
			int j1 = way[j0];
			pairV[j0] = pairV[j1];
			j0 = j1;
		} while(j0);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	memset(&cost, INF, sizeof cost);
	FOR1(i, n) FOR1(j, m) scanf("%d", &cost[i][j]);
	FOR(i, MAXN) FOR(j, i) {
		swap(cost[i][j], cost[j][i]);
	}
	swap(n, m);
	hungarian();
	return 0;
}