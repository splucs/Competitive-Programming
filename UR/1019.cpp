#include <cstdio>
int main()
{
    int N;
    scanf("%d", &N);
    printf("%d:%d:%d\n", N/3600, (N%3600)/60, N%60);
    return 0;
}
