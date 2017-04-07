#include <stdio.h>

int main(){
    float num[6], soma=0;
    int n=0;
    for (int i=0; i<6; i++){
        scanf("%f", &num[i]);
        if (num[i]>0){
            n++;
            soma+=num[i];
        }
    }
    soma/=n;
    printf ("%d valores positivos\n%g\n", n, soma);
    return 0;
}
