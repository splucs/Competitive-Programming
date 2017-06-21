#include <cstdio>
int f(int n, int k)
{
    if (n==1) return 1;
    else return (f(n-1, k)+k-1)%n+1;
}
int main()
{
    int NC, n, k, caso=0;
    scanf("%d", &NC);
    while (NC-->0)
    {
        caso++;
        scanf("%d %d", &n, &k);
        printf("Case %d: %d\n", caso, f(n,k));
    }
    return 0;
}
