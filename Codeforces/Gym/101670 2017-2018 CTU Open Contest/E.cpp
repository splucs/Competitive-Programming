#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof y)
typedef long long ll;
typedef pair<int, int> ii;

char field[MAXN][MAXN];
int n, m;

void assign(int i, int j, char c) {
	//printf("(%d,%d) -> %c\n", i, j, c);
	if (i < 0 || j < 0 || i >= m || j >= m) return;
	field[i][j] = c;
}

int main() {
	while(scanf("%d %d", &m, &n) != EOF) {
		FOR(i, m) FOR(j, m) field[i][j] = '.';
		FOR(i, m) field[i][m] = 0;
		FOR(it, n) {
			int h, i, j;
			scanf("%d %d %d", &h, &j, &i);
			if (h > 0) h++;
			FOR(k, h) {
				assign(i+k, j-1, '/');
				assign(i+k, j+1, '\\');
				assign(i+k, j, '|');
			}
			assign(i, j-1, '_');
			assign(i, j+1, '_');
			if (h == 0) assign(i, j, 'o');
			else assign(i+h, j, '^');
		}
		FOR(i, m+2) printf("*");
		printf("\n");
		REP(i, m) printf("*%s*\n", field[i]);
		FOR(i, m+2) printf("*");
		printf("\n\n");
	}
	return 0;
}