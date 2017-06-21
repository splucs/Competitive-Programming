#include <cstdio>
void mergesort(int* vet, int* aux, int a, int b, int* inv){
    if (a==b) return;
    int med = (a+b)/2;
    mergesort(vet, aux, a, med, inv);
    mergesort(vet, aux, med+1, b, inv);
    int i=a, j=med+1, k=a;
    while(i<=med && j<=b){
        if (vet[i]<=vet[j]) aux[k++]=vet[i++];
        else{
            (*inv)+=med+1-i;
            aux[k++]=vet[j++];
        }
    }
    while(i<=med) aux[k++]=vet[i++];
    while (j<=b) aux[k++]=vet[j++];
    for (i=a; i<=b; i++) vet[i]=aux[i];
}
int main()
{
    int N;
    while(true){
        scanf("%d", &N);
        if (N==0) break;
        int vet[N], aux[N];
        for (int i=0; i<N; i++){
            scanf("%d", vet+i);
        }
        int inv=0;
        mergesort(vet, aux, 0, N-1, &inv);
        if (inv%2==0) printf("Carlos\n");
        else printf("Marcelo\n");
    }
    return 0;
}
