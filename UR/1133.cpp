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
    for (int i=X+1; i<Y; i++){
        if (i%5==2 || i%5==3) printf("%d\n", i);
    }
    return 0;
}
