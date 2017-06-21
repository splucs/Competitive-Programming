#include<cstdio>
#define PI 3.14159
int main()
{
    double A, B, C;
    scanf ("%lf %lf %lf", &A, &B, &C);
    double triangulo, circulo, trapezio, quadrado, retangulo;
    triangulo = A*C/2.0;
    circulo = PI * C*C;
    trapezio = (A+B)*C/2.0;
    quadrado = B*B;
    retangulo = A*B;
    printf("TRIANGULO: %.3f\n", triangulo);
    printf("CIRCULO: %.3f\n", circulo);
    printf("TRAPEZIO: %.3f\n", trapezio);
    printf("QUADRADO: %.3f\n", quadrado);
    printf("RETANGULO: %.3f\n", retangulo);
    return 0;
}
