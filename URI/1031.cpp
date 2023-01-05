#include <cstdio>
int f(int n, int k)
{
    if (n==1) return 1;
    else return (f(n-1, k)+k-1)%n+1;
}
int main()
{
    int N;
    while (true)
    {
        scanf ("%d", &N);
        if (N==0) break;
        int i;
        for (i=1; f(N-1, i)!=12; i++);
        printf("%d\n", i);
    }
    return 0;
}
