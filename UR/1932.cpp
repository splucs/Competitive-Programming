#include <cstdio>

int v[200009], c[200009], vet[200009], N, C;

int max(int a, int b){
	if(a>b) return a;
	return b;
}

int comprar(int n);

int vender(int n){
	if (n==N-1) return vet[n];
	if (v[n]>=0) return v[n];
	v[n] = max(vet[n] + comprar(n+1), vender(n+1));
	return v[n];
}

int comprar(int n){
	if (n==N-1) return 0;
	if(c[n]>=0) return c[n];
	c[n] = max(vender(n+1) - vet[n] - C, comprar(n+1));
	return c[n];
}

int main()
{
	scanf("%d %d", &N, &C);
	for(int i=0; i<N; i++){
		c[i]=v[i]=-1;
		scanf("%d", vet+i);
	}
	printf("%d\n", comprar(0));
	return 0;
}