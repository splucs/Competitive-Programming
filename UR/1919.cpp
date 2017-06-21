#include <cstdio>

int vet[5];
int nres;

void verify(int p, int n, int K, int soma){
	if (p==4){
		if (soma==K){
			printf("{%d,%d,%d,%d,%d}\n", vet[0], vet[1], vet[2], vet[3], vet[4]);
			nres++;
		}
		return;
	}
	for (int i=n+1; i<10; i++){
		if (soma+i<=K){
			vet[p+1]=i;
			verify(p+1, i, K, soma+i);
		}
	}
}

int main()
{
	int T, K;
	bool possible;
	scanf("%d", &T);
	for (int t=0; t<T; t++){
		nres=0;
		scanf("%d", &K);
		if (K%(24*11111)!=0){
			printf("impossivel\n\n");
			continue;
		}
		K/=24*11111;
		verify(-1, -1, K, 0);
		if (nres==0) printf("impossivel\n\n");
		else printf("\n");
	}
	return 0;
}