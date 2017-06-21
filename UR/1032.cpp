#include <cstdio>
#define M 32612
int p[3502];
int f(int n, int k)
{
    if (n==1) return 1;
    else return (f(n-1, k+1)+p[k]-1)%n+1;
}
int main()
{
    int k=1;
    bool primos[M];
    for (int i=0; i<M; i++) primos[i]=true;
    for (int i=2; i<M; i++)
    {
        if (primos[i])
        {
            p[k++]=i;
            if (k==3502) break;
            for (int j=2*i;j<M; j+=i)
            {
                primos[j]=false;
            }
        }
    }
    int N;
    while (true)
    {
        scanf("%d", &N);
        if (N==0) break;
        printf("%d\n", f(N,1));
    }
    return 0;
}
