#include <bits/stdc++.h>
using namespace std;
#define INF 100009

int ceil(int a, int b) {
	if (a%b == 0) return a/b;
	else return a/b + 1;
}

int floor(int a, int b) {
	return a/b;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	int mx = INF, mn = 1, a, b;
	while(k --> 0) {
		scanf("%d %d", &a, &b);
		mn = max(mn, ceil(a, b));
		if (b>1) mx = min(mx, floor(a-1, b-1));
	}
	int ans = ceil(n, mn);
	if (mn > mx) ans = -1;
	for(int i=mn+1; i<=mx; i++) {
		if (ceil(n, i) != ans) ans = -1;
	}
	printf("%d\n", ans);
	return 0;
}