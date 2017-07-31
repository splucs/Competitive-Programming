#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

typedef long long ll;
ll pascal[MAXN][MAXN];

int main() {
	for(int n=0; n<MAXN; n++) {
		for(int k=0; k<MAXN; k++) {
			if (k > n) pascal[n][k] = 0;
			else if (k == 0 || n == k) pascal[n][k] = 1;
			else pascal[n][k] = pascal[n-1][k] + pascal[n-1][k-1];
		}
	}
	int T, N, left, V1, V2, W;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d %d %d", &N, &V1, &V2, &W);
		left = N - V1 - V2;
		ll winpos = 0, totpos = (1LL << left);
		for(int i=0; i<=left; i++) {
			if (2*(V1 + i) > N) winpos += pascal[left][i];
			//printf("prob de vencer %d de %d: %.3f\n", i, left, pascal[left][i]*1.0/totpos);
		}
		if (winpos == 0) printf("RECOUNT!\n");
		else if (winpos*100LL > ((ll)W)*totpos) printf("GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!\n");
		else printf("PATIENCE, EVERYONE!\n");
	}
	return 0;
}