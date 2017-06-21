#include <cstdio>
int main()
{
    int NUMBER, A;
    double B, SALARY;
    scanf("%d %d %lf", &NUMBER, &A, &B);
    SALARY = B* (double)A;
    printf("NUMBER = %d\nSALARY = U$ %.2f\n", NUMBER, SALARY);
    return 0;
}
