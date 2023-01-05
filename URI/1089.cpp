#include <cstdio>
int main()
{
    int N, picos;
    bool subindo;
    while (true){
        scanf("%d", &N);
        if (N==0) break;
        int H[N];
        picos=0;
        for (int i=0; i<N; i++){
            scanf("%d", H+i);
        }
        if (H[0]>H[N-1])subindo=true;
        else subindo =false;
        for (int i=1; i<=N; i++){
            if (subindo && H[i%N]<H[i-1]){
                picos++;
                subindo=false;
            }
            if(!subindo && H[i%N]>H[i-1]){
                picos++;
                subindo=true;
            }
        }
        printf("%d\n", picos);
    }
    return 0;
}
