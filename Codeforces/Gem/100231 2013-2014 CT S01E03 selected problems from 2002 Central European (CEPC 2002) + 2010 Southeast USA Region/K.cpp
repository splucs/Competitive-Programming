#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)

int main() {
	int a, ans, cur, N;
	while(scanf("%d", &N), N) {
		cur = 0;
		ans = -INF;
		for(int i=1; i<=N; i++) {
			scanf("%d", &a);
			cur = max(a, a+cur);
			ans = max(ans, cur);
		}
		printf("%d\n", ans);
	}
	return 0;
}