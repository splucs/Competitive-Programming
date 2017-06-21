#include <cstdio>
int main(){
    int a[3], maior;
    scanf ("%d", &a[0]);
    maior = a[0];
    scanf ("%d", &a[1]);
    if (maior < a[1]) maior = a[1];
    scanf ("%d", &a[2]);
    if (maior < a[2]) maior = a[2];
    printf("%d eh o maior\n", maior);
    return 0;
}
