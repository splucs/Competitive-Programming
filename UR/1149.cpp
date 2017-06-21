#include <cstdio>

int main()
{
	int A, N, res;
	scanf("%d", &A);
	do{
		scanf("%d", &N);
	}while(N<=0);
	res=0;
	for (int i = 0; i < N; ++i)
	{
		res+=A+i;
	}
	printf("%d\n", res);
	return 0;
}