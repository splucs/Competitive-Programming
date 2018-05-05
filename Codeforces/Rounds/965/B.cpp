#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int n, k;
char field[MAXN][MAXN];
int ans[MAXN][MAXN];

void check(int si, int sj) {
	bool ok = true;
	for(int di = 0; di < k && ok; di++) {
		int i = si + di;
		if (i >= n || field[i][sj] == '#') ok = false;
	}
	for(int di = 0; di < k && ok; di++) ans[si+di][sj]++;
	ok = true;
	for(int dj = 0; dj < k && ok; dj++) {
		int j = sj + dj;
		if (j >= n || field[si][j] == '#') ok = false;
	}
	for(int dj = 0; dj < k && ok; dj++) ans[si][sj+dj]++;
}

int main () {
	scanf("%d %d", &n, &k);
	FOR(i, n) scanf(" %s", field[i]);
	memset(&ans, 0, sizeof ans);
	FOR(i, n) FOR(j, n) check(i, j);
	int si = -1, sj = -1;
	FOR(i, n) FOR(j, n) {
		if (si == -1 || ans[si][sj] < ans[i][j]) {
			si = i; sj = j;
		}
	}
	printf("%d %d\n", si+1, sj+1);
	return 0;
}