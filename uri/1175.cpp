#include <cstdio>

int main()
{
	int N[20];
	for (int i = 0; i < 20; ++i)
	{
		scanf("%d", N+i);
	}
	for (int i = 0; i < 20; ++i)
	{
		printf("N[%d] = %d\n", i, N[19-i]);
	}
	return 0;
}