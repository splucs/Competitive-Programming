#define MAXN 59
#include <cstdio>

/*
 * Polyomino iteration
 */

int N, M;
int num[MAXN][MAXN], qi[MAXN*MAXN], qj[MAXN*MAXN];
int field[MAXN][MAXN], par[MAXN][MAXN];
int di[4] = {0, 1, 0, -1};
int dj[4] = {-1, 0, 1, 0};
int cnt;

void assign(int i, int j, int k) {
	qi[k] = i; qj[k] = j; num[i][j] = k;
}

#define valid(i, j) (i >= 0 && i < N && j >= 0 && j < M)

int iterate(int k, int h) {
	if (h == 0) return 0;
	int i = qi[k], j = qj[k], ni, nj;
	for(int d = 0; d < 4; d++) {
		ni = i + di[d]; nj = j + dj[d];
		if (!valid(ni, nj)) continue;
		if (num[ni][nj] == 0) {
			par[ni][nj] = k;
			assign(ni, nj, ++cnt);
		}
	}
	int ans = 0, cur;
	for(int t = k+1; t <= cnt; t++) {
		cur = iterate(t, h-1);
		if (cur > ans) ans = cur;
	}
	for(int d = 0; d < 4; d++) {
		ni = i + di[d]; nj = j + dj[d];
		if (!valid(ni, nj)) continue;
		if (par[ni][nj] == k) {
			par[ni][nj] = 0; cnt--;
			assign(ni, nj, 0);
		}
	}
	return ans + field[i][j];
}

/*
 * URI 1712
 */

#include <cstdio>
#include <cstring>

int main() {
	int K;
	while(scanf("%d %d", &N, &K)!=EOF) {
		M = N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &field[i][j]);
			}
		}
		int ans = 0;
		memset(&num, 0, sizeof num);
		memset(&par, 0, sizeof par);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cnt = 0;
				assign(i, j, ++cnt);
				int cur = iterate(1, K);
				if (cur > ans) ans = cur;
				num[i][j] = -1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}