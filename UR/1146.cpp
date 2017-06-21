#include <cstdio>

int main()
{
	int N;
	while(true){
		scanf("%d", &N);
		if (N==0) break;
		for (int i = 1; i <= N; ++i)
		{
			printf("%d", i);
			if (i<N) printf(" ");
			else printf("\n");
		}
	}
	return 0;
}