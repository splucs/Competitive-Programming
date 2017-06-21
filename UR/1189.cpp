#include <cstdio>

int main()
{
    double M[12][12], sum=0;
    char T;
    scanf("%c", &T);
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            scanf("%lf", &M[i][j]);
        }
    }
    for (int i = 0; i < 12; ++i)
    {
        for (int j = i+1; j < 11-i; ++j)
        {
            sum+=M[j][i];
        }
    }
    if (T=='M') sum/=30.0;
    printf("%.1f\n", sum);
    return 0;
}
