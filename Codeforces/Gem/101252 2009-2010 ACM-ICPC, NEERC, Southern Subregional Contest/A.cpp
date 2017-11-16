#include <bits/stdc++.h>
using namespace std;
#define MAXN 509

int b[MAXN][MAXN], N, M;
bool vis[MAXN][MAXN];
char path[MAXN];

int check(int j, int i) {
	int ans = b[i][j];
	if (!vis[i][j]) b[i][j] >>= 1;
	vis[i][j] = true;
	return ans;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%d %d", &N, &M);
	memset(&b, 0, sizeof b);
	memset(&vis, 0, sizeof vis);
	char c;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=M; j++) {
			scanf(" %c", &c);
			b[i][j] = c - '0';
		}
	}
	int x = 1, y = 1, dx = 1, dy = 0;
	scanf(" %s", path);
	int len = strlen(path), ans = 0;
	for(int k=0; k<len; k++) {
		if (path[k] == 'R') {
			if (dx == 1) dy = 1, dx = 0;
			else if (dy == 1) dy = 0, dx = -1;
			else if (dx == -1) dy = -1, dx = 0;
			else if (dy == -1) dy = 0, dx = 1;
		}
		else if (path[k] == 'L') {
			if (dx == 1) dy = -1, dx = 0;
			else if (dy == 1) dy = 0, dx = 1;
			else if (dx == -1) dy = 1, dx = 0;
			else if (dy == -1) dy = 0, dx = -1;
		}
		else {
			if (dx == 1) ans += check(x, y) + check(x, y-1);
			else if (dy == 1) ans += check(x, y) + check(x-1, y);
			else if (dx == -1) ans += check(x-1, y) + check(x-1, y-1);
			else if (dy == -1) ans += check(x-1, y-1) + check(x, y-1);
			x += dx;
			y += dy;
		}
	}
	printf("%d\n", ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}