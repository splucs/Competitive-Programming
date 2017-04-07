#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < 1000; ++i)
	{
		printf("N[%d] = %d\n", i, i%T);
	}
	return 0;
}