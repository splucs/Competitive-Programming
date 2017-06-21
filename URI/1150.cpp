#include <cstdio>

int main(){
	int X, N;
	scanf("%d", &X);
	do{
		scanf("%d", &N);
	}while (N<=X);
	int res=0, i=0;
	for (; res<=N; ++i)
	{
		res+=X+i;
	}
	printf("%d\n", i);
	return 0;
}