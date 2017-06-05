#include <cstdio>
#define MAXN 100009

long long int inv;

void mergesort(int* vet, int* aux, int a, int b){
	if (a==b) return;
	int med = (a+b)/2;
	mergesort(vet, aux, a, med);
	mergesort(vet, aux, med+1, b);
	int p=a, q=med+1, k=a;
	while(p<=med && q<=b){
		if (vet[p]>vet[q]){
			aux[k++]=vet[q++];
			inv += (long long int)(q-k);
		}
		else aux[k++]=vet[p++];
	}
	while(p<=med) aux[k++]=vet[p++];
	while(q<=b) aux[k++]=vet[q++];
	for(int i=a; i<=b; i++) vet[i]=aux[i];
}

int main()
{
	int N, vet[MAXN], aux[MAXN];
	inv=0;
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d", vet+i);
	}
	mergesort(vet, aux, 0, N-1);
	printf("inv = %lld:", inv);
	for(int i=0; i<N; i++){
		printf(" %d", vet[i]);
	}
	printf("\n");
	return 0;
}