#include <cstring>
#define MAXN 2009
#define MAXM 2009
#define INF 0x3f3f3f3f

/*
 * Hungarian's Algorithm O(n^2 m)
 * linhas de 1 a n, colunas de 1 a n
 */

int n, m;
int pu[MAXN], pv[MAXN], cost[MAXN][MAXM];
int pairV[MAXN], way[MAXM], minv[MAXM];
bool used[MAXM];

void hungarian() {
	memset(&pairV, 0, sizeof pairV);
	for(int i = 1, j0 = 0; i <= n; i++) {
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

/*
 * Codeforces 101635G
 */

#include <cstdio>
#include <algorithm>
using namespace std;

int bx[MAXN], by[MAXN], cx[MAXM], cy[MAXM], rx, ry;

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &bx[i], &by[i]);
	}
	for(int j = 1; j <= m; j++) {
		scanf("%d %d", &cx[j], &cy[j]);
	}
	scanf("%d %d", &rx, &ry);

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m+n-1; j++) {
			if (j <= m) cost[i][j] = abs(bx[i]-cx[j]) + abs(by[i]-cy[j]);
			else cost[i][j] = abs(bx[i]-rx) + abs(by[i]-ry);
			//printf("%d ", cost[i][j]);
		}
		//printf("\n");
	}

	int ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += abs(bx[i]-rx) + abs(by[i]-ry);
	}
	m += n-1;
	hungarian();
	for(int j = 1; j <= m; j++) {
		if (pairV[j] == 0) continue;
		ans += cost[pairV[j]][j];
	}
	printf("%d\n", ans);
	return 0;
}