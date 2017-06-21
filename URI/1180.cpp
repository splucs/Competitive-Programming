#include <cstdio>

int main()
{
	int N, X, pos, menor;
	scanf("%d", &N);
	scanf("%d", &X);
	menor=X;
	pos=0;
	for (int i = 1; i < N; ++i)
	{
		scanf("%d", &X);
		if (X<menor){
			menor=X;
			pos=i;
		}
	}
	printf("Menor valor: %d\nPosicao: %d\n", menor, pos);
	return 0;
}