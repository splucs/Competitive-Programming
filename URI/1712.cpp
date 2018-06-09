#define MAXN 59

/*
 * Polyomino iteration
 */

int N, M;
int num[MAXN][MAXN], qi[MAXN*MAXN], qj[MAXN*MAXN];
int field[MAXN][MAXN], par[MAXN][MAXN];
int di[4] = {0, 1, 0, -1};
int dj[4] = {-1, 0, 1, 0};
int cnt;

int sop[MAXN], sh[MAXN], sk[MAXN], ss[MAXN], sz;

#define assign(i, j, k) qi[k] = i; qj[k] = j; num[i][j] = k
#define valid(i, j) (i >= 0 && i < N && j >= 0 && j < M)
#define push(h, k, s) \
sop[++sz] = 3; sh[sz] = h; sk[sz] = k; ss[sz] = s;\
sop[++sz] = 2; sh[sz] = h; sk[sz] = k; ss[sz] = s;\
sop[++sz] = 1; sh[sz] = h; sk[sz] = k; ss[sz] = s

int iterate(int si, int sj, int H) {
	cnt = 1; assign(si, sj, cnt);
	sz = 0;
	push(H, 1, 0);
	int ans = 0;
	while(sz) {
		int op = sop[sz], k = sk[sz];
		int h = sh[sz], s = ss[sz--];
		int i = qi[k], j = qj[k], ni, nj;
		s += field[i][j];
		if (s > ans) ans = s;
		if (h == 1) continue;
		for(int d = 0; op == 1 && d < 4; d++) {
			ni = i + di[d]; nj = j + dj[d];
			if (!valid(ni, nj)) continue;
			if (num[ni][nj] == 0) {
				par[ni][nj] = k; cnt++;
				assign(ni, nj, cnt);
			}
		}
		for(int t = k+1; op == 2 && t <= cnt; t++) {
			push(h-1, t, s);
		}
		for(int d = 0; op == 3 && d < 4; d++) {
			ni = i + di[d]; nj = j + dj[d];
			if (!valid(ni, nj)) continue;
			if (par[ni][nj] == k) {
				par[ni][nj] = 0; cnt--;
				assign(ni, nj, 0);
			}
		}
	}
	return ans;
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
				int cur = iterate(i, j, K);
				if (cur > ans) ans = cur;
				num[i][j] = -1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
