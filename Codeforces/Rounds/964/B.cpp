#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)

int main() {
	int n, A, B, C, T;
	scanf("%d %d %d %d %d", &n, &A, &B, &C, &T);
	int ans = 0;
	FOR(i, n) {
		int t;
		scanf("%d", &t);
		if (B > C) {
			ans += A;
		}
		else {
			ans += A + (C-B)*(T-t);
		}
	}
	printf("%d\n", ans);
	return 0;
}
