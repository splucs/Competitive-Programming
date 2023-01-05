#include <bits/stdc++.h>
using namespace std;

int main() {
	int T, N, M;
	scanf("%d", &T);
	while(T --> 0) {
		int am = 0, x, ans = 1;
		scanf("%d %d", &N, &M);
		for(int i = 0; i < N; i++) {
			scanf("%d", &x);
			if (am+x > M) {
				am = x;
				ans++;
			}
			else am += x;
		}
		printf("%d\n", ans);
	}
	return 0;
}