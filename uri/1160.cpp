#include <stdio.h>
int main(){
    int T, PA, PB, n;
    double G1, G2;
    scanf ("%d", &T);
    for (int i=0; i<T; i++){
        scanf ("%d %d %lf %lf", &PA, &PB, &G1, &G2);
        n=0;
        while(PA<=PB && n<=100){
            PA=(int)(PA*(1.0+G1/100.0));
            PB=(int)(PB*(1.0+G2/100.0));
            n++;
        }
        if (n>100) printf ("Mais de 1 seculo.\n");
        else printf ("%d anos.\n", n);
    }
    return 0;
}
