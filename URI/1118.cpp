#include <cstdio>
int main()
{
    double x, y;
    int repetir;
    do{
        do{
            scanf("%lf", &x);
            if (x<0.0 || x>10.0) printf("nota invalida\n");
        }while(x<0.0 || x>10.0);
        do{
            scanf("%lf", &y);
            if (y<0.0 || y>10.0) printf("nota invalida\n");
        }while(y<0.0 || y>10.0);
        printf("media = %.2f\n", (x+y)/2.0);
        do{
            printf("novo calculo (1-sim 2-nao)\n");
            scanf("%d", &repetir);
        }while(repetir!=1 && repetir!=2);
    }while(repetir==1);
    return 0;
}
