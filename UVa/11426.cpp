#include <cstdio>
#define MAXN 4000009

typedef unsigned long long ll;
int phi[MAXN], sievesize;
ll F[MAXN];

void gcdSieve(int n) {
	sievesize = n+1;
	for(int i=0; i<= sievesize; i++) phi[i] = F[i] = 0;
	for(int i = 1; i <= sievesize; i++) {
		phi[i] += i;
		for(int j = i; j <= sievesize; j += i) {
			if (j > i) phi[j] -= phi[i];
			F[j] += j / i * phi[i];
		}
	}
}

ll sum[MAXN];
 
int main() {
	gcdSieve(MAXN-2);
	sum[0] = 0;
	for(int i=1; i<MAXN; i++) sum[i] = F[i] + sum[i-1];
	ll N;
	while(scanf("%llu", &N), N) {
		printf("%llu\n", sum[N] - N*(N+1)/2);
	}
	return 0;
}