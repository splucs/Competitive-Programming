#include <bits/stdc++.h>
#define FOR(x,n) for(int x=0;x<n;x++)
#define MAXN 60
using namespace std;
typedef long long int ll;

int n, a[MAXN];
int dp[MAXN];

int main() {
	scanf("%d", &n);
	FOR(i, n) {
		scanf("%d", &a[i]);
		if (i == 0) {
			dp[i] = 1;
		}
		else {
			dp[i] = 1 + dp[i-1];
			int j = i;
			while(j > 0 && a[j-1] >= a[j]) {
				j--;
				dp[i] = min(dp[i], 1 + (j-1 >= 0 ? dp[j-1] : 0));
			}
		}
	}
	printf("%d\n", dp[n-1]);
	return 0;
}
