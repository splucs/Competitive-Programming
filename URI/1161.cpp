#include <cstdio>

int main()
{
	int M, N;
	long long int fat1, fat2;
	while(scanf("%d %d", &M, &N)!=EOF){
		fat1 = fat2 = 1;
		for (int i = 2; i <= M; ++i)
		{
			fat1*=i;
		}
		for (int i = 2; i <= N; ++i)
		{
			fat2*=i;
		}
		printf("%lld\n", fat1+fat2);
	}
	return 0;
}