#include <cstdio>

int main()
{
	int N, X, soma;
	scanf("%d", &N);
	while(N-->0){
		scanf("%d", &X);
		soma = 0;
		for (int i = 1; i < X; ++i)
		{
			if (X%i==0) soma+=i;
		}
		if (soma==X) printf("%d eh perfeito\n", X);
		else printf("%d nao eh perfeito\n", X);
	}
	return 0;
}