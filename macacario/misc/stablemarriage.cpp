#include <cstdio>
#include <cstring>
#define MAXN 1009

int m, n, p[MAXN];
int L[MAXN][MAXN], R[MAXN][MAXN];
int R2L[MAXN], L2R[MAXN];

void stableMarriage() {
	memset(R2L, -1, sizeof(R2L));
	memset(p, 0, sizeof(p));
	for (int i = 0, wom, hubby; i < m; i++) {
		for (int man = i; man >= 0;) {
			while (true) {
				wom = L[man][p[man]++];
				if (R2L[wom] < 0 || R[wom][man] > R[wom][R2L[wom]]) break;
			}
			hubby = R2L[wom];
			R2L[L2R[man] = wom] = man;
			man = hubby;
		}
	}
}