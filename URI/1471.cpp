#include <cstdio>
#include <cstring>
#define MAXN 10009

int main()
{
    int N, R, x;
    bool survived[MAXN], hasprinted;
    while(scanf("%d %d", &N, &R)!=EOF){
        memset(&survived, false, sizeof survived);
        hasprinted = false;
        for(int i=0; i<R; i++){
            scanf("%d", &x);
            survived[x] = true;
        }
        for(int i=1; i<=N; i++){
            if (survived[i]) continue;
            printf("%d ", i);
            hasprinted = true;
        }
        if (!hasprinted) printf("*");
        printf("\n");
    }
    return 0;
}
