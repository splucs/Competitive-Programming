#include <cstdio>
#define MAXN 100009
//O(nlogn), M[i] o índice do menor elemento que existe
//uma sequência de tamanho i que termina nele
int LIS(int* arr, int n){
	int M[end-arr+1], L=1, l, h, m;
	M[1]=0;
	for(int i=1; i<n; i++){
		if (arr[i]<arr[M[1]]){
			M[1]=i; continue;
		}
		l = 1; h = L+1;
		while(h>l+1){
			m = (l+h)/2;
			if (arr[M[m]]<arr[i]) l = m;	//estritamente crescente
			//if (arr[M[m]]<=arr[i]) l = m;	//crescente
			else h = m;
		}
		if (h>L) L=h;
		M[h] = i;
	}
	return L;
}

int main()
{
	int N, vet[MAXN], L;
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d", vet+i);
	}
	L = LIS(vet, vet+N);
	printf("LIS length = %d\n", L);
	return 0;
}