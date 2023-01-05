#include <cstdio>

typedef long long ll;

int main(){
	int P, Q, N;
	ll x[20];
	x[0] = 0;
	x[1] = 1;
	scanf("%d %d %d", &P, &Q, &N);
	for(int i=2; i<=N; i++){
		x[i] = P*x[i-1] + Q*x[i-2];
	}
	printf("x(%d) = %d*x(%d) + %d*x(%d) = %I64d\n", N, P, N-1, Q, N-2, x[N]);
	return 0;
}