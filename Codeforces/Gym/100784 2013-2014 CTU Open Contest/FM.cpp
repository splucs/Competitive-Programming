#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int n, m, r, c;
char field[MAXN][MAXN];
int sum[MAXN][MAXN];

int get(int i, int j) {
	if (i < 0 || j < 0) return 0;
	if (i >= n) i = n-1;
	if (j >= m) j = m-1;
	return sum[i][j];
}

int simulate(int si, int sj) {
	int ans = 0;
	for(int i = si; i-r < n; i+=r) {
		for(int j = sj; j-c < m; j+=c) {
			if (get(i, j) - get(i-r, j) - get(i, j-c) + get(i-r, j-c) > 0)
				ans++;
		}
	}
	return ans;
}

int main() {
	while(scanf("%d %d %d %d", &n, &m, &r, &c) != EOF) {
		FOR(i, n) scanf(" %s", field[i]);
		FOR(i, n) FOR(j, m) {
			if (i == 0 && j == 0) sum[i][j] = 0;
			else if (i == 0) sum[i][j] = sum[i][j-1];
			else if (j == 0) sum[i][j] = sum[i-1][j];
			else sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
			if (field[i][j] == 'X') sum[i][j]++;
		}
		int ans = INF;
		FOR(i, r) FOR(j, c) ans = min(ans, simulate(i, j));
		printf("%d\n", ans);
	}
	return 0;
}