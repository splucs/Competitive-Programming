#include <cstdio>

int main()
{
	int C, N;
	scanf("%d", &C);
	int vet[1009], soma;
	double media;
	for (int caso = 1; caso <= C; ++caso)
	{
		scanf("%d", &N);
		soma=0;
		for (int i = 0; i < N; ++i)
		{
			scanf("%d", vet+i);
			soma+=vet[i];
		}
		media = soma/((double)N);
		soma = 0;
		for (int i = 0; i < N; ++i)
		{
			if (vet[i]>media) soma++;
		}
		printf("%.3f%%\n", soma*100.0/N);
	}
	return 0;
}