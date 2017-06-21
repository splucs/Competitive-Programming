#include <cstdio>
int main()
{
    int A, C, cont, ant, atual;
    while(true){
        scanf("%d %d", &A, &C);
        if (A==0 && C==0) break;
        ant=A;
        cont=0;
        for (int i=1; i<=C; i++){
            scanf("%d", &atual);
            if (atual<ant) cont+=ant-atual;
            ant=atual;
        }
        printf("%d\n", cont);
    }
    return 0;
}
