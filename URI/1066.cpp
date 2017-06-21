#include <stdio.h>

int main()
{
    int pos=0, neg=0, par=0, impar=0;
    for (int i=0; i<5; i++)
    {
        int x;
        scanf("%d", &x);
        if (x>0) pos++;
        if (x<0) neg++;
        if (x%2==0) par++;
        else impar++;
    }
    printf("%d valor(es) par(es)\n", par);
    printf("%d valor(es) impar(es)\n", impar);
    printf("%d valor(es) positivo(s)\n", pos);
    printf("%d valor(es) negativo(s)\n", neg);
    return 0;
}
