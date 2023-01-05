#include <cstdio>

int main()
{
    int P, k=1, cont=0;
    scanf("%d", &P);
    do{
        cont++;
        if(k>P/2) k = 2*(k-P/2)-1;
        else k = 2*k;
    }while(k!=1);
    printf("%d\n", cont);
}
