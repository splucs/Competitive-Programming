#include <cstdio>

typedef long long ll;

int main(){
	ll N;
	scanf("%I64d", &N);
	while(true){
		ll u = N%10LL;
		ll r = N/10LL;
		if (r-2*u < 0){
			
		}
		printf("%I64d + %I64d = %I64d e %I64d - %I64d = %I64d", u, u, 2*u, r, 2*u, r-2*u);
		N = r-2*u;
		if (N >= 100){
			printf("\n");
			continue;
		}
		else{
			if (N%7 == 0) printf(" que eh dividido por 7 = %I64d\n", N/7);
			else printf(" que nao eh dividido por 7\n");
			break;
		}
	}
	return 0;
}