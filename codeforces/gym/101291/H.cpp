#include <bits/stdc++.h>
using namespace std;
#define MAXN 60

char board[MAXN][MAXN];
int n, m;

void dfs(int i, int j)
{
	if (i < 0 || i >= n) return;
	if (j < 0 || j >= m) return;
	if (board[i][j] == 'W') return;
	board[i][j] = 'W';

	dfs(i - 1, j);
	dfs(i + 1, j);
	dfs(i, j - 1);
	dfs(i, j + 1);
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &board[i][j]);
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 'L') {
				dfs(i, j);
				ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}