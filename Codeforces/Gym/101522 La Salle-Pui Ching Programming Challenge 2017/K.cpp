#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int grid[MAXN][MAXN], N, M, K;

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for(int k=0, x, y; k<K; k++) {
		scanf("%d %d", &x, &y);
		grid[x][y] = 1;
	}
	int ans = 0;
	if (grid[1][1] == 0) {
		ans++;
		grid[1][1] = 1;
	}
	if (grid[1][M] == 0) {
		ans++;
		grid[1][M] = 1;
	}
	if (grid[N][1] == 0) {
		ans++;
		grid[N][1] = 1;
	}
	if (grid[N][M] == 0) {
		ans++;
		grid[N][M] = 1;
	}
	printf("%d\n", ans);
	return 0;
}
