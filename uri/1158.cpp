#include <cstdio>

int main()
{
	int N, X, Y, soma;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d %d", &X, &Y);
		if (X%2==0) X++;
		soma=0;
		for (int j = 0; j < Y; ++j)
		{
			soma+=X+(2*j);
		}
		printf("%d\n", soma);
	}
	return 0;
}