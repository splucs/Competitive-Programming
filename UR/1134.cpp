#include <stdio.h>

int main(){
    int x=0, gas=0, alc=0, die=0;
    printf ("MUITO OBRIGADO\n");
    while (x!=4){
        scanf("%d", &x);
        if (x==1)
            alc++;
        if (x==2)
            gas++;
        if (x==3)
            die++;
    }
    printf ("Alcool: %d\n", alc);
    printf ("Gasolina: %d\n", gas);
    printf ("Diesel: %d\n", die);
    return 0;
}
