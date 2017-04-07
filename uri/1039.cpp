#include <cstdio>
int main()
{
    int R1, X1, Y1, R2, X2, Y2;
    while(scanf("%d %d %d %d %d %d", &R1, &X1, &Y1, &R2, &X2, &Y2)!=EOF)
    {
        if (R1>R2 && (R1-R2)*(R1-R2)>=(X1-X2)*(X1-X2) + (Y1-Y2)*(Y1-Y2)) printf("RICO\n");
        else printf("MORTO\n");
    }
    return 0;
}
