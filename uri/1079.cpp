#include <cstdio>
int main()
{
    int N;
    scanf("%d", &N);
    double a, b, c;
    for (int i=0; i<N; i++){
        scanf("%lf %lf %lf", &a, &b, &c);
        printf("%.1f\n", (2*a+3*b+5*c)/10.0);
    }
    return 0;
}
