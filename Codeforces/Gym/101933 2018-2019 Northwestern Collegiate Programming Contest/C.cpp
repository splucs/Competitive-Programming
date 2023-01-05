#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define mset(x, y) memset(&x, y, sizeof x)

int x[MAXN];

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		mset(x, 0);
		FOR(i, n) {
			int pos;
			scanf("%d", &pos);
			x[pos]++;
		}
		int cur = 0, cnt = 0;
		int ans = 0;
		FOR(i, MAXN) {
			cur += cnt;
			if (cur >= 20) {
				ans++;
				cur = cnt = 0;
			}
			cnt += x[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}