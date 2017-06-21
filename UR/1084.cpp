#include <cstdio>
#define MAXN 100009

char vet[MAXN], pilha[MAXN];

int main(){
	int N, D, top;
	while (scanf ("%d %d", &N, &D), (N||D)){
		scanf(" %s", vet);
		top = -1;
		for (int i=0; i<N; i++){
			while (top >= 0 && pilha[top]<vet[i] && D>0){
				top--; D--;
			}
			pilha[++top] = vet[i];
		}
		top -= D;
		pilha[++top] = '\0';
		printf("%s\n", pilha);
	}
	return 0;
}