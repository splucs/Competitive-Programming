#include <bits/stdc++.h>
using namespace std;
#define MAXN 209
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)

char field[5][4] = {
	{'1','2','3','*'},
	{'4','5','6','*'},
	{'7','8','9','*'},
	{'*','0','*','*'},
	{'*','*','*','*'},
};

bool vis[5][4][MAXN];
int ans, target;

void bt(int i, int j, int cur) {
	if (cur > MAXN || vis[i][j][cur]) return;
	vis[i][j][cur] = true;
	//printf("%d,%d,%d\n", i, j, cur);
	if (field[i][j] == '*') return;
	bt(i+1, j, cur);
	bt(i, j+1, cur);
	FOR(k, 4) {
		cur = cur*10 + field[i][j] - '0';
		if (abs(ans-target) > abs(cur-target)) ans = cur;
		bt(i+1, j, cur);
		bt(i, j+1, cur);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	ans = 0;
	FOR1(t, T) {
		scanf("%d", &target);
		FOR(i, 5) FOR(j, 4) FOR(cur, MAXN) vis[i][j][cur] = false;
		bt(0, 0, 0);
		printf("%d\n", ans);
	}
	return 0;
}