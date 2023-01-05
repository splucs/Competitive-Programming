#include <cstdio>

long long int s(long long int n){
	return n*n;
}

int main()
{
	int N, d1, d2, b1, b2;
	long long int CX, CY, R1, R2, X, Y;
	while(true){
		scanf("%d", &N);
		if (N==0) break;
		scanf("%lld %lld %lld %lld", &CX, &CY, &R1, &R2);
		d1=d2=b1=b2=0;
		for (int i=0; i<N; i++){
			scanf("%lld %lld", &X, &Y);
			if (s(X-CX)+s(Y-CY)<s(R1)) d1++;
			else if (s(X-CX)+s(Y-CY)<=s(R2)) b1++;
			scanf("%lld %lld", &X, &Y);
			if (s(X-CX)+s(Y-CY)<s(R1)) d2++;
			else if (s(X-CX)+s(Y-CY)<=s(R2)) b2++;
		}
		if (d1>d2) printf("C > P\n");
		else if (d1<d2) printf("P > C\n");
		else if (b1>b2) printf("C > P\n");
		else if (b1<b2) printf("P > C\n");
		else printf("C = P\n");
	}
	return 0;
}