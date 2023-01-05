#include <cstdio>
#include <cmath>
int main()
{
    double a, b, c, delta;
    scanf("%lf %lf %lf", &a, &b, &c);
    delta = b*b - 4*a*c;
    if (delta<0 || a==0) printf("Impossivel calcular\n");
    else{
        double R1, R2;
        R1=(-1.0*b + sqrt(delta))/(2.0*a);
        R2=(-1.0*b - sqrt(delta))/(2.0*a);
        printf("R1 = %.5f\nR2 = %.5f\n", R1, R2);
    }
    return 0;
}
