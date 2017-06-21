#include <cstdio>

int main()
{
	int T, N, vet[1009];
	int contador;
	int atual, ultimo, maximo, noprato;
	scanf("%d", &T);
	for (int caso = 1; caso <= T; ++caso)
	{
		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
		{
			scanf("%d", vet+i);
		}
		ultimo=vet[0];
		contador=0;
		for (int i = 1; i < N; ++i)
		{
			if (vet[i]<ultimo) contador+=ultimo-vet[i];
			ultimo = vet[i];
		}
		printf("Case #%d: %d ", caso, contador);
		maximo=0;
		for (int i = 1; i < N; ++i)
		{
			maximo=(maximo>vet[i-1]-vet[i]?maximo:vet[i-1]-vet[i]);
		}
		contador=0;
		noprato=vet[0];
		for (int i = 1; i < N; ++i)
		{
			if (noprato>=maximo){
				noprato-=maximo;
				contador+=maximo;
			}
			else{
				contador+=noprato;
				noprato=0;
			}
			noprato=vet[i];
		}
		printf("%d", contador);
		if (caso<T) printf("\n");
	}
	return 0;
}