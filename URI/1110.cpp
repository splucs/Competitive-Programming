#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <queue>

int main(){
    while (true){
        int n, k=0;
        scanf ("%d", &n);
        if (n==0)
            break;
        int discarded[n];
        std::queue <int> pilha;
        for (int m=1; m<=n; m++){
            pilha.push(m);
        }
        while (pilha.size()>=2){
            discarded[k]=pilha.front();
            k++;
            pilha.pop();
            pilha.push(pilha.front());
            pilha.pop();
        }
        printf ("Discarded cards:");
        for (int m=0; m<k-1; m++){
            printf (" %d,", discarded[m]);
        }
        printf (" %d\n", discarded[k-1]);
        printf ("Remaining card: %d\n", pilha.front());
    }
    return 0;
}
