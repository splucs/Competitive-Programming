#include <cstdio>
int main()
{
    int B, N, D, V, C;
    bool crise;
    while(true){
        scanf("%d %d", &B, &N);
        if (B==0 && N==0) break;
        int saldo[B];
        for (int i=0; i<B; i++) scanf("%d", saldo+i);
        for (int i=0; i<N; i++){
            scanf("%d %d %d", &D, &C, &V);
            saldo[C-1]+=V;
            saldo[D-1]-=V;
        }
        crise=false;
        for (int i=0; i<B && !crise; i++){
            if (saldo[i]<0) crise=true;
        }
        if (crise) printf("N\n");
        else printf("S\n");
    }
    return 0;
}
