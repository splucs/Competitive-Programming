#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
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

int dp[MAXN][3], N;
int col[256];
char arr[MAXN];

int main() {
	col['C'] = 0;
	col['M'] = 1;
	col['Y'] = 2;
	col['c'] = 0;
	col['m'] = 1;
	col['y'] = 2;
	scanf("%d", &N);
	FOR(i, N) scanf(" %c", &arr[i]);
	FOR(i, N) FOR(c, 3) {
		if (i == 0) {
			if(arr[i] == '?' || c == col[arr[i]]) dp[i][c] = 1;
			else dp[i][c] = 0;
		}
		else if (arr[i] != '?' && c != col[arr[i]]) dp[i][c] = 0;
		else {
			int ans = 0;
			FOR(k, 3) {
				if (k != c) ans += dp[i-1][k];
			}
			ans = min(ans, 2);
			dp[i][c] = ans;
		}
	}
	int ans = dp[N-1][0] + dp[N-1][1] + dp[N-1][2];
	ans = min(ans, 2);
	if (ans >= 2) printf("Yes\n");
	else printf("No\n");
	return 0;
}