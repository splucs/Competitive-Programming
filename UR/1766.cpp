#include <cstdio>
#include <cstring>
typedef struct rena{
    char nome[100];
    int peso;
    int idade;
    double altura;
} rena;
bool operator <(const rena a, const rena b){
    if (a.peso>b.peso) return true;
    if (a.peso<b.peso) return false;
    if (a.idade<b.idade) return true;
    if (a.idade>b.idade) return false;
    if (a.altura<b.altura) return true;
    if (a.altura>b.altura) return false;
    if (0>strcmp(a.nome, b.nome)) return true;
    else return false;
}
void mergesort(int a, int b, rena* vet, rena* aux){
    if(a==b) return;
    int med=(a+b)/2;
    mergesort(a, med, vet, aux);
    mergesort(med+1, b, vet, aux);
    int i=a, j=med+1, k=a;
    while(i<=med && j<=b){
        if(vet[i]<vet[j]) aux[k++]=vet[i++];
        else aux[k++]=vet[j++];
    }
    while(i<=med) aux[k++]=vet[i++];
    while(j<=b) aux[k++]=vet[j++];
    for(int l=a; l<=b; l++) vet[l]=aux[l];
}
int main()
{
    int T, N, M;
    scanf("%d", &T);
    for (int caso=1; caso<=T; caso++){
        scanf("%d %d", &N, &M);
        rena renas[N];
        rena aux[N];
        for (int i=0; i<N; i++){
            scanf(" %s %d %d %lf", renas[i].nome, &renas[i].peso, &renas[i].idade, &renas[i].altura);
        }
        mergesort(0, N-1, renas, aux);
        printf("CENARIO {%d}\n", caso);
        for (int i=1; i<=M; i++){
            printf("%d - %s\n", i, renas[i-1].nome);
        }
    }
    return 0;
}
