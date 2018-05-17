#include <bits/stdc++.h>
using namespace std;
#define MAXN 309
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
#define EPS 1e-9

int cnt[MAXN][MAXN];
char s[MAXN];

int main() {
	int n;
	memset(&cnt, 0, sizeof cnt);
	scanf("%d %s", &n, s);
	int ans = 0;
	FOR(i, n) {
		if (i == 0) continue;
		cnt[s[i-1]][s[i]]++;
		ans = max(ans, cnt[s[i-1]][s[i]]);
	}
	FOR(i, MAXN) FOR(j, MAXN) {
		if (ans == cnt[i][j]) {
			printf("%c%c\n", i, j);
			return 0;
		}
	}
	return 0;
}