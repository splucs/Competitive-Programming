#include <cstdio>

int main()
{
	int vet[10009], N, media, npassos;
	while(scanf("%d", &N)!=EOF){
		media=0;
		for (int i = 0; i < N; ++i)
		{
			scanf("%d", vet+i);
			media+=vet[i];
		}
		if (media%N!=0){
			printf("-1\n");
			continue;
		}
		media/=N;
		npassos=0;
		for (int i = 0; i < N; ++i)
		{
			if(vet[i]>media) npassos+=vet[i]-media;
		}
		printf("%d\n", npassos+1);
	}
	return 0;
}