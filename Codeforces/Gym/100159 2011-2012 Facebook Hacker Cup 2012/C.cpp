#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MOD 4207849484LL

typedef long long ll;
ll dp[MAXN];
char str[MAXN];

int main() {
	int T, M;
	scanf("%d", &T);
	for(int cases = 1; cases<=T; cases++) {
		scanf("%d %s", &M, str+1);
		dp[0] = 1;
		int N = strlen(str+1);
		for(int i=1; i<=N; i++) {
			int ans = 0, p=1;
			dp[i] = 0;
			for(int j=i; j>0; j--) {
				ans += (str[j]-'0')*p;
				p *= 10;
				if (ans > M) break;
				if (str[j] == '0') continue;
				dp[i] += dp[j-1];
				dp[i] %= MOD;
			}
			//printf("dp[%d] = %I64d\n", i, dp[i]);
		}
		printf("Case #%d: %I64d\n", cases, dp[N]);
	}
	return 0;
}