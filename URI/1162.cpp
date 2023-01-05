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
    int N, L, inv;
    scanf("%d", &N);
    int vet[60], aux[60];
    while(N-->0){
        scanf("%d", &L);
        for (int i=0; i<L; i++){
            scanf("%d", vet+i);
        }
        inv=0;
        if (L>0) mergesort(vet, aux, 0, L-1, &inv);
        printf("Optimal train swapping takes %d swaps.\n", inv);
    }
    return 0;
}