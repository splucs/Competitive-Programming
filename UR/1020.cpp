#include <cstdio>
int main()
{
    int N;
    scanf("%d", &N);
    printf("%d ano(s)\n%d mes(es)\n%d dia(s)\n", N/365, (N%365)/30, (N%365)%30);
    return 0;
}
