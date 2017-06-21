#include <cstdio>
int main()
{
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);
    if (a+b>c && a+c>b && b+c>a && a>0 && b>0 && c>0) printf("Perimetro = %.1f\n", a+b+c);
    else printf("Area = %.1f\n", c*(a+b)/2.0);
    return 0;
}
