#include <cstdio>
int main()
{
    int X, Y, res;
    scanf("%d %d", &X, &Y);
    if (X%(Y-X)==0) res = Y/(Y-X);
    else res = Y/(Y-X) + 1;
    printf("%d\n", res);
    return 0;
}
