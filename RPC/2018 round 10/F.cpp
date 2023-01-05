#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define MAXN 50009

int p[5] = {2, 3, 4, 7, 13};
int pell[MAXN][5];

int main() {
	FOR(j, 5) {
		pell[0][j] = 0;
		pell[1][j] = 1;
	}
	for(int i = 2; i < MAXN; i++) {
		FOR(j, 5) {
			pell[i][j] = (2*pell[i-1][j] + pell[i-2][j])%p[j];
		}
	}
	int a;
	while(scanf("%d", &a) != EOF) {
		bool ok = false;
		FOR(j, 5) {
			if (!pell[a][j]) {
				printf("Pell's number %d is divisible by %d\n", a, p[j]);
				ok = true;
			}
		}
		if (!ok) printf("-1\n");
	}
	return 0;
}