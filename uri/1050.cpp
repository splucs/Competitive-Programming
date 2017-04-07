#include <cstdio>
int main()
{
    int d;
    scanf("%d", &d);
    if (d==61) printf("Brasilia\n");
    else if (d==71) printf("Salvador\n");
    else if (d==11) printf("Sao Paulo\n");
    else if (d==21) printf("Rio de Janeiro\n");
    else if (d==32) printf("Juiz de Fora\n");
    else if (d==19) printf("Campinas\n");
    else if (d==27) printf("Vitoria\n");
    else if (d==31) printf("Belo Horizonte\n");
    else printf("DDD nao cadastrado\n");
    return 0;
}
