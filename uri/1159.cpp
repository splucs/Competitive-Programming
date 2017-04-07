#include <stdio.h>

int main(){
    bool primeiro = true;
    while (true){
        if (!primeiro) printf ("\n");
        int num, soma=0;
        scanf ("%d", &num);
        if (num==0) break;
        if (num%2==1 || num%2==-1) num++;
        printf ("%d", (num+4)*5);
        primeiro = false;
    }
    return 0;
}
