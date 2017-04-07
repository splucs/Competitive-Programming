#include <cstdio>
#include <cstring>
int main()
{
    char nome[100];
    double A, B, TOTAL;
    scanf("%s", nome);
    scanf ("%lf %lf", &A, &B);
    TOTAL = A + 0.15 * B;
    printf ("TOTAL = R$ %.2f\n", TOTAL);
    return 0;
}
