#include <cstdio>
int main()
{
    int n=0;
    double x;
    for (int i=0; i<6; i++)
    {
        scanf("%lf", &x);
        if (x>0) n++;
    }
    printf("%d valores positivos\n", n);
    return 0;
}
