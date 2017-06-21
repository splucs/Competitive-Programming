#include <cstdio>

int main()
{
	int N, X;
	unsigned long long int g;
	scanf("%d", &N);
	while(N-->0){
		scanf("%d", &X);
		g=1;
		for (int i = 1; i < X; i++)
		{
			g*=2;
		}
		printf("%llu kg\n", g/6000);
	}
	return 0;
}