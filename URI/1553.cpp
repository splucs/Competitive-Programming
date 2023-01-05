#include <stdio.h>

int main(){
    while (true){
        int N, K;
        scanf ("%d %d", &N, &K);
        if (N==0 && K==0) break;
        int q[100] = {0};
        int x;
        for (int i=0; i<N; i++){
            scanf("%d", &x);
            x--;
            q[x]++;
        }
        x=0;
        for (int i=0; i<100; i++){
            if(q[i]>=K) x++;
        }
        printf ("%d\n", x);
    }
    return 0;
}
