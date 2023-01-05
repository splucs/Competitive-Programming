#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 300009
#define INF 0x3f3f3f3f

int n, m;
char str[MAXN];
int back[MAXN];
int dp[2][MAXN], st[2][MAXN], top[2];

int check(int w) {
	int ans = 0;
	FOR(k, 2) while(top[k]) {
		int j = st[k][--top[k]];
		dp[k][j] = 0;
	}
	for(int l = 0, r, k = 0; l < m; l = r + 2, k ^= 1) {
		r = l + w;
		if (r >= m) r = m - 1;
		else r = back[r] - 1;
		if (r < l) {
			ans = -INF;
			break;
		}
		while(top[k]) {
			int j = st[k][--top[k]];
			dp[k][j] = 0;
		}
		for(int i = back[r]; i >= l; i = back[i-1]) {
			int j = i-l;
			st[k][top[k]++] = j;
			dp[k][j] = 1;
			if (dp[k][j] < 1 + dp[k^1][j-1])
				dp[k][j] = 1 + dp[k^1][j-1];
			if (dp[k][j] < 1 + dp[k^1][j])
				dp[k][j] = 1 + dp[k^1][j];
			if (j+1 < w && dp[k][j] < 1 + dp[k^1][j+1])
				dp[k][j] = 1 + dp[k^1][j+1];
			if (ans < dp[k][j])
				ans = dp[k][j];
		}
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	m = 0;
	FOR(i, n) {
		scanf(" %s", str + m);
		while(str[m]) m++;
		str[m++] = ' ';
	}
	str[--m] = 0;
	int last = -1;
	FOR(i, m) {
		if (str[i] == ' ') last = i;
		back[i] = last;
	}
	int ans = 0, val = -INF;
	FOR1(i, m) {
		int cur = check(i);
		if (cur > val) {
			val = cur;
			ans = i;
		}
	}
	printf("%d %d\n", ans, val);
	return 0;
}