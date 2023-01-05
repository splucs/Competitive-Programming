#include <cstdio>
int main()
{
    double precos[6];
    precos[1]=4.00;
    precos[2]=4.50;
    precos[3]=5.00;
    precos[4]=2.00;
    precos[5]=1.50;
    int x, y;
    scanf("%d %d", &x, &y);
    printf("Total: R$ %.2f\n", y*precos[x]);
    return 0;
}
