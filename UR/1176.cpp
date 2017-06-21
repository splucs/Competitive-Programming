#include <cstdio>

int main()
{
	unsigned long long int fib[61];
	fib[0]=0;
	fib[1]=1;
	for (int i = 2; i < 61; ++i)
	{
		fib[i]=fib[i-1]+fib[i-2];
	}
	int N, T;
	scanf("%d", &T);
	while(T-->0){
		scanf("%d", &N);
		printf("Fib(%d) = %llu\n", N, fib[N]);
	}
	return 0;
}