#include <cstdio>

int main()
{
    int X, Y, aux, soma=0;
    scanf("%d %d", &X, &Y);
    if (X>Y) {
        aux = X;
        X = Y;
        Y = aux;
    }
    for (int i=X; i<=Y; i++){
        if (i%13!=0) soma+=i;
    }
    printf("%d\n", soma);
    return 0;
}
