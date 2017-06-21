#include <cstdio>
void mergesort(int a, int b, int* vet, int* aux){
    if(a==b) return;
    int med=(a+b)/2;
    mergesort(a, med, vet, aux);
    mergesort(med+1, b, vet, aux);
    int i=a, j=med+1, k=a;
    while(i<=med && j<=b){
        if(vet[i]<=vet[j]) aux[k++]=vet[i++];
        else aux[k++]=vet[j++];
    }
    while(i<=med) aux[k++]=vet[i++];
    while(j<=b) aux[k++]=vet[j++];
    for(int l=a; l<=b; l++) vet[l]=aux[l];
}
int needed;
int pos(int* vet, int a, int b, int comp){
    if (b<a || needed==0) return 0;
    if (vet[b]==comp){
        needed--;
        return 1+pos(vet, a, b-1, comp);
    }
    if (vet[a]==comp){
        needed--;
        return 1+pos(vet, a+1, b, comp);
    }
    if (a==b) return 0;
    if (vet[a]+vet[b]==comp){
        needed--;
        return 2+pos(vet, a+1, b-1, comp);
    }
    if (vet[a]+vet[b]>comp) return pos(vet, a, b-1, comp);
    if (vet[a]+vet[b]<comp) return pos(vet, a+1, b, comp);
}
int main()
{
    int M, N, L, K, minimo1, minimo2;
    while (true)
    {
        scanf("%d %d", &M, &N);
        if (M==0 && N==0) break;
        scanf("%d %d", &L, &K);
        int tabuas[K], aux[K];
        for (int i=0; i<K; i++) scanf("%d", tabuas+i);
        mergesort(0, K-1, tabuas, aux);
        minimo2=minimo1=-1;
        if ((M*100)%L==0){
            needed=(M*100)/L;
            minimo1=pos(tabuas, 0, K-1, N);
            if (needed>0) minimo1=-1;
        }
        if ((N*100)%L==0){
            needed=(N*100)/L;
            minimo2=pos(tabuas, 0, K-1, M);
            if (needed>0) minimo2=-1;
        }
        if (minimo1==-1 && minimo2==-1) printf("impossivel\n");
        else if (minimo1==-1) printf("%d\n", minimo2);
        else if (minimo2==-1) printf("%d\n", minimo1);
        else printf("%d\n", (minimo1>minimo2?minimo2:minimo1));
    }
    return 0;
}
