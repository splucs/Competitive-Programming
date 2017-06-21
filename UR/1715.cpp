#include <cstdio>
int main()
{
    int N, M, cont=0, aux;
    bool x;
    scanf("%d %d", &N, &M);
    for (int i=0; i<N; i++){
        x=true;
        for (int j=0; j<M; j++){
            scanf("%d", &aux);
            if (aux<=0) x = false;
        }
        if (x) cont++;
    }
    printf("%d\n", cont);
    return 0;
}
