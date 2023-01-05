#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    int contador=1;
    while (true){
        int N, Q, valor;
        scanf ("%d %d", &N, &Q);
        if (N==0 && Q==0)
            break;
        printf ("CASE# %d:\n", contador);
        int vet[N+1];
        for (int m=0; m<N; m++){
            scanf ("%d", &valor);
            vet[m]=valor;
        }
        sort (vet, vet+N);
        map<int, int> fila;
        for(int m=0; m<N; m++){
            if (!fila.count(vet[m]))
                fila[vet[m]]=m+1;
        }
        for (int m=1; m<=Q; m++){
            scanf ("%d", &valor);
            if (fila.count(valor)){
                printf ("%d found at %d\n", valor, fila[valor]);
            }
            else {
                printf ("%d not found\n", valor);
            }
        }
        contador++;
    }
    return 0;
}
