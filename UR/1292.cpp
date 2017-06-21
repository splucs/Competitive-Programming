#include <cstdio>
#include <cmath>

int main()
{
    double P;
    while (scanf("%lf", &P)!=EOF)
    {
        printf ("%.10lf\n", P*sin(3*M_PI/5)/sin(13*M_PI/20));
    }
    return 0;
}
