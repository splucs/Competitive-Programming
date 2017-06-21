#include <cstdio>

bool isSqrt(int n){
	for (int i = 0; i*i <= n; ++i)
	{
		if (i*i==n) return true;
	}
	return false;
}

int main()
{
	int T, N, vet[50], n, i;
	scanf("%d", &T);
	while(T-->0){
		scanf("%d", &N);
		for (i = 0; i < N; ++i)
		{
			vet[i]=0;
		}
		n=1;
		while(true){
			for (i = 0; i < N; ++i)
			{
				if (vet[i]==0 || isSqrt(vet[i]+n)){
					vet[i]=n;
					break;
				}
			}
			if (i==N) break;
			n++;
		}
		printf("%d\n", n-1);
	}
}