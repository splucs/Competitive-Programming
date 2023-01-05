#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

typedef long long ll;
ll ndiv[MAXN], sum[MAXN];

int main() {
	memset(&ndiv, 0, sizeof ndiv);
	for(int i=1; i<MAXN; i++) {
		for(int j=i; j<MAXN; j+=i) {
			ndiv[j]+=i;
		}
	}
	sum[0] = 0;
	for(int i=1; i<MAXN; i++) sum[i] = ndiv[i] + sum[i-1];
	int N;
	while(scanf("%d", &N), N) {
		printf("%lld\n", sum[N]);
	}
	return 0;
}