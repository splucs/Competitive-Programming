#include <cstdio>

int main()
{
	int N, fat;
	scanf("%d", &N);
	fat=1;
	for (int i = 2; i <= N; ++i)
	{
		fat*=i;
	}
	printf("%d\n", fat);
	return 0;
}