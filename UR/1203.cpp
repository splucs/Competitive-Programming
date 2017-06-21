#include <cstdio>

int pd[109][5000];
int vet[109];

bool Q(int i, int S){
	if (S<0 || i<0) return false;
	if (pd[i][S]>=0) return pd[i][S];
	pd[i][S]=Q(i-1, S) || vet[i]==S || Q(i-1, S-vet[i]);
	return pd[i][S];
}

int main()
{
	int A, B, R, K;
	while(scanf("%d %d", &R, &K)!=EOF){
		for (int i = 0; i < R; ++i)
		{
			vet[i]=0;
			for (int j=0; j<=K; j++)
			{
				pd[i][j]=-1;
			}
		}
		for (int i = 0; i < K; ++i)
		{
			scanf("%d %d", &A, &B);
			vet[A-1]++;
			vet[B-1]++;
		}
		if (Q(R-1, K)) printf("S\n");
		else printf("N\n");
	}
	return 0;
}