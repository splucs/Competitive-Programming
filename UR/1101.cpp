#include <cstdio>
int main()
{
    int M, N , Sum;
    while(true){
        scanf("%d %d", &M, &N);
        if (M==0 || N==0) break;
        if (M>N){
            Sum=N;
            N=M;
            M=Sum;
        }
        Sum=0;
        for (int i=M; i<=N; i++){
            printf("%d ", i);
            Sum+=i;
        }
        printf("Sum=%d\n", Sum);
    }
    return 0;
}
