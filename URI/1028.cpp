#include <cstdio>
int mdc(int x, int y)
{
    if (y==0) return x;
    else return mdc(y, x%y);
}
int main()
{
    int N, x, y;
    scanf ("%d", &N);
    while (N-->0)
    {
        scanf("%d %d", &x, &y);
        printf("%d\n", mdc(x,y));
    }
    return 0;
}
