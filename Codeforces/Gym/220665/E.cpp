#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define MAXN 2009

char d;
int M, dp[MAXN][MAXN][2], pow10[MAXN];

int computeDp(char *str) {
	int len = strlen(str);
	for(int i = len; i >= 0; i--) {
		for(int r = 0; r < M; r++) {
			for(int force = 0; force <= 1; force++) {
				bool even = i % 2 != 0;
				if (i == len) dp[r][i][force] = (r == 0 ? 1 : 0);
				else {
					dp[r][i][force] = 0;
					char lo = even ? d : '0';
					char hi = min(even ? d : '9', force ? str[i] : '9');
					for (char c = lo; c <= hi; c++) {
						if (!even && c == d) continue;
						dp[r][i][force] += dp[(r + (c-'0')*pow10[i]) % M][i+1][(force && c == str[i]) ? 1 : 0];
						dp[r][i][force] %= MOD;
					}
				}
			}
		}
	}
	return dp[0][0][1];
}

bool checkd(char *str) {
	int rem = 0;
	int len = strlen(str);
	for(int i = 0; i < len; i++) {
		if (i % 2 == 0 && str[i] == d) return false;
		if (i % 2 != 0 && str[i] != d) return false;
	}
	for(int i = 0; i < len; i++) {
		rem += ((str[i]-'0')*pow10[i]) % M;
		rem %= M;
	}
	return rem == 0;
}

char num1[MAXN], num2[MAXN];

int main() {
	scanf("%d %c %s %s", &M, &d, num1, num2);
	int ans = 0;

	int len = strlen(num1);
	pow10[len-1] = 1;
	for(int i = len-2; i >= 0; i--) {
		pow10[i] = (10*pow10[i+1]) % M;
	}
	if (checkd(num1)) ans++;
	ans += computeDp(num2) - computeDp(num1);

	while (ans < 0) ans += MOD;
	ans %= MOD;

	printf("%d\n", ans);
	return 0;
}