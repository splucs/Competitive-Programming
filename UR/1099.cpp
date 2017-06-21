#include <cstdio>
int main()
{
    int N, X, Y, cont;
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%d %d", &X, &Y);
        if (X>Y){
            cont=X;
            X=Y;
            Y=cont;
        }
        if(X%2!=0) X++;
        if (Y%2!=0) Y--;
        cont =0;
        for (int j=X+1; j<Y; j+=2) cont+=j;
        printf("%d\n", cont);
    }
    return 0;
}
