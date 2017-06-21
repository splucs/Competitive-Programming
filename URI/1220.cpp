#include <cstdio>

int abs(int x){
	if (x<0) return -x;
	else return x;
}
int main()
{
	int n, soma, media, vet[1009];
	int dol, cent, soma1, soma2;
	while(true){
		scanf(" %d", &n);
		if (n==0) break;
		soma=0;
		for (int i = 0; i < n; ++i)
		{
			scanf(" %d.%d ", &dol, &cent);
			vet[i]=dol*100+cent;
			soma+=vet[i];
		}
		media = soma/n;
		soma1 = soma2 = 0;
		for (int i = 0; i < n; ++i)
		{
			if (vet[i]>=media+1) soma1+=vet[i]-media-1;
			else soma2+=media-vet[i];
		}
		if (soma2>soma1) soma = soma2;
		else soma = soma1;
		printf("$%d.%02d\n", soma/100, soma%100);
	}
	return 0;
}