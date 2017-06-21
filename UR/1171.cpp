#include <stdio.h>

void mergevet(int a, int b, int *vet, int *aux){
    int med=(a+b)/2;
    int i=a;
    int j=med+1;
    int k=0;

    while(i<=med && j<=b){
        if(vet[i]<=vet[j]){
            aux[k++]=vet[i++];
        }
        else{
            aux[k++]=vet[j++];
        }
    }

    while(i<=med){
        aux[k++]=vet[i++];
    }
    while(j<=b)
        aux[k++]=vet[j++];

    for(int l=a; l<=b; l++){
        vet[l]=aux[l-a];
    }
}

void mergesort(int a, int b, int *vet, int *aux){
    if(a==b)
        return;
    int med=(a+b)/2;
    mergesort(a, med, vet, aux);
    mergesort(med+1, b, vet, aux);

    mergevet(a, b, vet, aux);
}

int main(){
    int N;
    scanf("%d", &N);
    int vet[N], aux[N];
    for (int i=0; i<N; i++){
        scanf ("%d", &vet[i]);
    }
    mergesort(0, N-1, vet, aux);
    int cont=1;
    for (int i=1; i<N; i++){
        if (vet[i]==vet[i-1]){
            cont++;
        }
        else {
            printf ("%d aparece %d vez(es)\n", vet[i-1], cont);
            cont=1;
        }
    }
    printf ("%d aparece %d vez(es)\n", vet[N-1], cont);
    return 0;
}
