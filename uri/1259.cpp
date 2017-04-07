#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define INF 0x3f3f3f3f
#define MAX 100005

bool ordena(int a, int b){
    if (a%2!=b%2)
        return a%2<b%2;
    if (a%2==0)
        return a<b;
    return a>b;
}
int main() {
    int vet[MAX];
    int n;

    scanf("%d", &n);

    for (int i=0; i<n; i++){
        scanf ("%d", &vet[i]);
    }
    sort(vet, vet+n, ordena);

    for (int i=0; i<n; i++){
        printf ("%d\n", vet[i]);
    }
    return 0;
}
