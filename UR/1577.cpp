#include <stdio.h>

int main(){
    int N;
    scanf ("%d", &N);
    for (int z=0; z<N; z++){
        int n;
        scanf ("%d", &n);
        while (n%2==0){
            n /=2;
        }
        if (n%3==0)
            n /=3;
        if (n%5==0)
            n /=5;
        if (n%17==0)
            n /=17;
        if (n%257==0)
            n /=257;
        if (n%65537==0)
            n /=65537;
        if (n==1)
            printf ("Yes\n");
        else printf ("No\n");
    }
    return 0;
}
