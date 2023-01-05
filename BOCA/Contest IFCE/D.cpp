#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, ans = 1;
	scanf("%d", &N);
	while(N != 1) {
		if (N%2 == 0) N /= 2;
		else N = 3*N+1;
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}