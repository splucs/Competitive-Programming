#include <cstdio>
#include <cmath>
int main()
{
    double p, q;
    int EV1, EV2, AT, D;
    while(true){
        scanf("%d %d %d %d", &EV1, &EV2, &AT, &D);
        if (EV1==0 && EV2==0 && AT==0 && D==0) break;
        if (EV1%D!=0){
            EV1+=D-EV1%D;
        }
        EV1/=D;
        if (EV2%D!=0){
            EV2+=D-EV2%D;
        }
        EV2/=D;
        if (AT==3) printf("%.1f\n", 100*EV1/((double)(EV1+EV2)));
        else printf("%.1f\n", 100*(1.0-pow((6.0-AT)/(double)AT, EV1))/(1.0-pow((6.0-AT)/(double)AT, EV1+EV2)));
    }
    return 0;
}
