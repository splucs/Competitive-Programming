#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MOD 1000000009LL

typedef long long ll;
ll fat[MAXN], pascal[MAXN][4];

int main() {
	for(int n=0; n<MAXN; n++) {
		for(int k=0; k<4; k++) {
			if (k > n) pascal[n][k] = 0;
			else if (k == 0 || n == k) pascal[n][k] = 1;
			else pascal[n][k] = (pascal[n-1][k] + pascal[n-1][k-1]) % MOD;
		}
	}
	fat[0] = 1;
	for(int i=1; i<MAXN; i++) fat[i] = (i*fat[i-1])%MOD;
	int N;
	while(scanf("%d", &N), N) {
		printf("%lld\n", (pascal[N][3]*fat[N-3])%MOD);
	}
	return 0;
}