#include <bits/stdc++.h>
using namespace std;
#define MAXN 60

char board[MAXN][MAXN];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &board[i][j]);
		}
	}
	for (int j = 0; j < m; j++) {
		int last = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (board[i][j] == '#') last = i - 1;
			if (board[i][j] == 'o') {
				swap(board[last][j], board[i][j]);
				last--;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
	return 0;
}