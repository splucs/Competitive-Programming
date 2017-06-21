#include <cstdio>

int main()
{
	int N;
	scanf("%d", &N);
	int x=1;
	for (int i = 0; i < 4*N; ++i, ++x)
	{
		if (x%4!=0) printf("%d ", x);
		else printf("PUM\n");
	}
	return 0;
}