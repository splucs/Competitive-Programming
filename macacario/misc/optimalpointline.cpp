#include <cstdio>
#include <cstring>
#define MAXN 1009

int mat[MAXN][MAXN], n;	//0-indexed

void magicsquare() {
	int i = n - 1, j = n / 2;
	memset(&mat, 0, sizeof mat);
	for (int k = 1; k <= n*n; k++) {
		mat[i][j] = k;
		if (mat[(i + 1) % n][(j + 1) % n] > 0) {
			i = (i - 1 + n) % n;
		}
		else {
			i = (i + 1) % n;
			j = (j + 1) % n;
		}
	}
}