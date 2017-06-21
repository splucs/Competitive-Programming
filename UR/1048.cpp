#include <cstdio>
int main()
{
    double salario;
    int reajuste;
    scanf("%lf", &salario);
    if (salario<=400) reajuste = 15;
    else if (salario<=800) reajuste = 12;
    else if (salario<=1200) reajuste = 10;
    else if (salario<=2000) reajuste = 7;
    else reajuste = 4;
    printf("Novo salario: %.2f\nReajuste ganho: %.2f\nEm percentual: %d %\n", salario*(100.0+reajuste)/100.0, salario*(reajuste/100.0), reajuste);
    return 0;
}
