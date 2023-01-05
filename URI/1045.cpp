#include <cstdio>
#include <algorithm>
int main()
{
    double lados[3];
    scanf("%lf %lf %lf", lados, lados+1, lados+2);
    std::sort(lados, lados+3);
    if (lados[2]>=lados[0]+lados[1]) printf("NAO FORMA TRIANGULO\n");
    else{
        if (lados[2]*lados[2]==lados[0]*lados[0] + lados[1]*lados[1]) printf("TRIANGULO RETANGULO\n");
        else if (lados[2]*lados[2]>lados[0]*lados[0] + lados[1]*lados[1]) printf("TRIANGULO OBTUSANGULO\n");
        else if (lados[2]*lados[2]<lados[0]*lados[0] + lados[1]*lados[1]) printf("TRIANGULO ACUTANGULO\n");
        if (lados[0]==lados[1] && lados[0]==lados[2]) printf("TRIANGULO EQUILATERO\n");
        else if (lados[0]==lados[1] || lados[2]==lados[1] || lados[0]==lados[2]) printf("TRIANGULO ISOSCELES\n");
    }
    return 0;
}
