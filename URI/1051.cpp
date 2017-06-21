#include <cstdio>
int main()
{
    double s;
    scanf("%lf", &s);
    if (s<=2000)printf("Isento\n");
    else if (s<=3000)printf("R$ %.2f\n", (s-2000.0)*0.08);
    else if (s<=4500)printf("R$ %.2f\n", 80 + (s-3000.0)*0.18);
    else printf("R$ %.2f\n", 350 + (s-4500.0)*0.28);
    return 0;
}
