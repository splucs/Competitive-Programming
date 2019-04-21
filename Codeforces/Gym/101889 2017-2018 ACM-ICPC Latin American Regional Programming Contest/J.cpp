#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009
#define MAXLOGN 20
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;

int n;
char s[MAXN];

bool simulate(int si, int k) {
	if (s[si] == 'P') return false;
	for(int i = (si+k)%n; i != si; i = (i+k)%n) {
		if (s[i] == 'P') return false;
	}
	return true;
}

int dp[MAXN];

int main() {
	scanf(" %s", s);
	n = strlen(s);
	int ans = 0;
	FOR1(k, n-1) {
		int g = __gcd(k, n);
		if (k == g) FOR(i, k) {
			if (simulate(i, k)) dp[g] = 1;
		}
		ans += dp[g];
	}
	printf("%d\n", ans);
	return 0;
}