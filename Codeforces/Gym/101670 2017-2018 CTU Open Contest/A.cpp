#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
typedef long long ll;

ll a[MAXN];

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		FOR1(i, n) scanf("%lld", &a[i]);
		if (n == 1) {
			printf("1\n");
			continue;
		}
		int ans = n-1;
		ll r = a[n] - a[n-1];
		REP1(i, n-2) {
			if (a[i+1] - a[i] == r) ans--;
			else break;
		}
		printf("%d\n", ans);
	}
	return 0;
}