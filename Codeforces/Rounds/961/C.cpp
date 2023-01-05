#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

char chess[MAXN][MAXN];
int n, diff[2][4];

int checkdiff(int c) {
	FOR(i, n) FOR(j, n) {
		if (chess[i][j] == '0') diff[1 - (i+j)%2][c]++;
		else if (chess[i][j] == '1') diff[(i+j)%2][c]++;
	}
}

int main() {
	scanf("%d", &n);
	FOR(c, 4) {
		FOR(i, n) scanf(" %s", chess[i]);
		checkdiff(c);
	}
	sort(diff[0], diff[0]+4);
	sort(diff[1], diff[1]+4);
	if (n % 2 == 0) {
		int s0 = 0;
		FOR(c, 4) s0 += diff[0][c];
		int s1 = 0;
		FOR(c, 4) s1 += diff[1][c];
		printf("%d\n", min(s0, s1));
	}
	else {
		int ans = diff[0][0] + diff[0][1] + diff[1][0] + diff[1][1];
		printf("%d\n", ans);
	}
	return 0;
}