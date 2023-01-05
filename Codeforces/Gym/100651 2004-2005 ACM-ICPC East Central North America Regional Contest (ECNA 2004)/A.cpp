#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

int dp[MAXN];
char str[MAXN];

int main() {
	while(true) {
		scanf(" %s", str);
		if (!strcmp(str, "0")) break;
		int N = strlen(str);
		for(int i=0; i<N; i++) {
			dp[i] = 0;
			if (i >= 0) {
				int one = (str[i]-'0');
				if (one <= 26 && one >= 1) dp[i] += (i >= 1 ? dp[i-1] : 1);
			}
			if(i >= 1) {
				int two = (str[i]-'0') + 10*(str[i-1]-'0');
				if (two <= 26 && two >= 10) dp[i] += (i >= 2 ? dp[i-2] : 1);
			}
		}
		printf("%d\n", dp[N-1]);
	}
	return 0;
}