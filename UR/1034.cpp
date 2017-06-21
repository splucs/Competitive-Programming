#include <cstdio>
int main()
{
    int T, N, M;
    scanf("%d", &T);
    while (T-->0)
    {
        scanf("%d %d", &N, &M);
        int moedas[N];
        for(int i=0; i<N;i++)
        {
            scanf("%d", moedas+i);
        }
        int pd[M+1], minimo;
        pd[0]=0;
        for (int i=1; i<=M; i++)
        {
            minimo = i;
            for (int j=0; j<N; j++)
            {
                if (i-moedas[j]>= 0 && minimo>pd[i-moedas[j]]) minimo=pd[i-moedas[j]];
            }
            pd[i]=minimo+1;
        }
        printf("%d\n", pd[M]);
    }
    return 0;
}
