#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define mset(x, y) memset(&x, y, sizeof x)

int a[2][3];

int main() {
	FOR(i, 2) FOR(j, 3) scanf("%d", &a[i][j]);
	int ans = 0;
	FOR(j, 3) ans += max(0, a[1][j] - a[0][j]);
	printf("%d\n", ans);
	return 0;
}