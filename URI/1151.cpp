#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    if (N==1) printf ("0");
    if (N==2) printf ("0 1");
    if (N>2) {
        printf ("0 1");
        int fib[N];
        fib[0]=0;
        fib[1]=1;
        for (int i=2; i<N; i++){
            fib[i]=fib[i-1]+fib[i-2];
            printf (" %d", fib[i]);
        }
    }
    printf ("\n");
    return 0;
}
