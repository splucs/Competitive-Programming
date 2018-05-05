#include <bits/stdc++.h>
using namespace std;
#define MAXN 159

int p[MAXN][MAXN];

int main() {
	int N;
	scanf("%d", &N);
	memset(&p, 0, sizeof p);
	p[0][0] = 1;
	p[1][1] = 1;
	for(int n = 2; n <= N; n++) {
		for(int i = 0; i <= n; i++) {
			p[n][i] = p[n-2][i];
			if (i > 0) p[n][i] += p[n-1][i-1];
			p[n][i] %= 2;
		}
	}
	printf("%d\n", N);
	for(int i = 0; i <= N; i++) {
		printf("%d ", p[N][i]);
	}
	printf("\n");
	printf("%d\n", N-1);
	for(int i = 0; i <= N-1; i++) {
		printf("%d ", p[N-1][i]);
	}
	printf("\n");
	return 0;
}