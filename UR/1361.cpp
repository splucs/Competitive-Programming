#include <stdio.h>
#include <map>
using namespace std;

int vet[500000];
int aux[500000];

void merge(int a, int b){
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

void mergesort(int a, int b){
    if(a==b)
        return;
    int med=(a+b)/2;
    mergesort(a, med);
    mergesort(med+1, b);

    merge(a, b);
}

int abs(int x){
    if (x>=0)
        return x;
    else return -1*x;
}
int main(){
    int p;
    scanf ("%d", &p);
    for (int pl=0; pl<p; pl++){
        map <int, int> ar;
        int n;
        scanf ("%d", &n);
        int mod[n];
        for (int i=0; i<n; i++){
            scanf ("%d", &mod[i]);
            vet[i]=abs(mod[i]);
            ar[vet[i]]=mod[i];
        }
        mergesort(0, n-1);
        for (int i=0; i<n; i++){
            vet[i]=ar[vet[i]];
        }
        int pivo=vet[0], contador=1;
        for (int i=1; i<n; i++){
            if (vet[i]*pivo<0){
                pivo=vet[i];
                contador++;
            }
        }
        printf ("%d\n", contador);
    }
    return 0;
}
