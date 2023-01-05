#include <stdio.h>

int main(){
    int fase = 0;
    float x, y, z;
    while (fase<2){
        if (fase==0){
            scanf("%f", &x);
            if (x>=0 && x<=10) fase++;
            else printf ("nota invalida\n");
        }
        else if (fase==1){
            scanf("%f", &y);
            if (y>=0 && y<=10) fase++;
            else printf ("nota invalida\n");
        }
    }
    printf ("media = %.2lf\n", (x+y)/2);
    return 0;
}
