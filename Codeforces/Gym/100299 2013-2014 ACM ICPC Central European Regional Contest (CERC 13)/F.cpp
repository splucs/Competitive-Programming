#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXLOGN 20
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
typedef long long ll;
typedef pair<int, int> ii;

char mat[12][12];
int bits[12][12];

int pd[10][10][1 << 16];
int iter[10][10][1 << 16];
int total_iter = 0;

int dx[4] = {-1, -1, 1, 1};
int dy[4] = {-1, 1, -1, 1};

int calc(int x, int y, int mask) {
	if (iter[x][y][mask] == total_iter) return pd[x][y][mask];

	int& ans = pd[x][y][mask];
	iter[x][y][mask] = total_iter;

	ans = 0;

	for (int k = 0; k < 4; k++) {
		int nx = x + dx[k], ny = y + dy[k];
		int mx = x + 2*dx[k], my = y + 2*dy[k];

		if (nx >= 0 && nx < 10 &&
			mx >= 0 && mx < 10 &&
			ny >= 0 && ny < 10 &&
			my >= 0 && my < 10);
		else continue;

		if (mat[nx][ny] == 'B' && mat[mx][my] == '#');
		else continue;

		int bit = bits[nx][ny];

		if (mask&(1 << bit)) continue;

		ans = max(ans, 1+calc(mx, my, mask|(1 << bit)));
	}

	return ans;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		FOR(i, 10) scanf(" %s", mat[i]);

		ii w;
		int ans = 0;
		FOR(i, 10) FOR(j, 10) {
			if (mat[i][j] != 'W') continue;

			w = ii(i, j);
			
			mat[i][j] = '#';

			int cnt = 0;
			FOR(x, 10) FOR(y, 10) {
				if (mat[x][y] != 'B') continue;
				if (x%2 == w.first%2 || y%2 == w.second%2) continue;
				if (x == 0 || x == 9 || y == 0 || y == 9) continue;

				bits[x][y] = cnt++;
			}
			assert(cnt <= 16);
			++total_iter;
	
			ans = max(ans, calc(w.first, w.second, 0));
			mat[i][j] = 'W';
		}

		printf("%d\n", ans);
	}

}
