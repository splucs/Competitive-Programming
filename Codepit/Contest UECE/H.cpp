#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

bool mirror[MAXN];
char carac[11] = {'A', 'H', 'I', 'M', 'O', 'T', 'U', 'V', 'W', 'X', 'Y'};
char str[MAXN], dp[MAXN][MAXN];

int main() {
	int T;
	scanf("%d", &T);
	memset(&mirror, false, sizeof mirror);
	for(int i=0; i<11; i++) {
		mirror[carac[i]] = true;
	}
	while(T-->0) {
		scanf(" %s", str);
		int len = strlen(str), ans = 0;
		for(int s=0; s<len; s++) {
			for(int i=0; i+s<len; i++) {
				int j = s+i;
				if (s == 0) dp[i][j] = mirror[str[i]];
				else {
					if (mirror[str[i]] && str[i] == str[j]) dp[i][j] = j>i+1 ? dp[i+1][j-1] : true;
					else dp[i][j] = false;
				}
				if (dp[i][j]) ans = max(ans, s+1);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}