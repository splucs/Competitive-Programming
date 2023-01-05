#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int gcd(int x, int y) {
	if (y == 0) return x;
	else return gcd(y, x%y);
}

int main() {
	int T, N, g, x;
	long long S;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		g = 0;
		S = 0;
		for(int i=0; i<N; i++) {
			scanf("%d", &x);
			g = gcd(g, x);
			S += x;
		}
		printf("%I64d %d\n", S, g);
	}
	return 0;
}