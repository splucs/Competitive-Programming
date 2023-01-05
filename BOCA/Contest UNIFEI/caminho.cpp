#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF (1LL<<60)

typedef long long ll;
ll dp[MAXN], arr[MAXN];
int prv[MAXN], N;

int main() {
	int T;
	scanf("%d", &T);
	for(int t=1; t<=T; t++) {
		scanf("%d", &N);
		N--;
		for(int i=0; i<N; i++) scanf("%lld", &arr[i]);
		ll mxjoy = 0;
		int si = -1, sj = -1;
		for(int i=0; i<N; i++) {
			if (i > 0 && dp[i-1] >= 0) {
				dp[i] = arr[i] + dp[i-1];
				prv[i] = prv[i-1];
			}
			else {
				dp[i] = arr[i];
				prv[i] = i;
			}
			
			if (dp[i] > mxjoy) {
				mxjoy = dp[i];
				si = prv[i];
				sj = i;
			}
			else if (dp[i] == mxjoy) {
				if (sj - si < i - prv[i]) {
					si = prv[i];
					sj = i;
				}
				else if (sj - si == i - prv[i] && si > prv[i]) {
					si = prv[i];
					sj = i;
				}
			}
		}
		
		if (mxjoy == 0) {
			printf("Trecho %d não tem partes agradaveis, pois %lld", t, arr[0]);
			ll sum = arr[0];
			for(int i=1; i<N; i++) {
				printf(" + %lld", arr[i]);
				sum += arr[i];
			}
			printf(" = %lld\n", sum);
		}
		else {
			printf("A parte mais agradavel do trecho %d está entre %d e %d, isto eh, %lld", t, si+1, sj+2, arr[si]);
			ll sum = arr[si];
			for(int i=si+1; i<=sj; i++) {
				printf(" + %lld", arr[i]);
				sum += arr[i];
			}
			printf(" = %lld\n", sum);
		}
	}
	return 0;
}