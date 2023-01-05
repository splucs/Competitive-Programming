#include <cstdio>
int main()
{
    int C=0, R=0, S=0, N, total;
    char c;
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf(" %d %c", &total, &c);
        if (c=='C') C+=total;
        if (c=='R') R+=total;
        if (c=='S') S+=total;
    }
    total=C+R+S;
    printf("Total: %d cobaias\n", total);
    printf("Total de coelhos: %d\n", C);
    printf("Total de ratos: %d\n", R);
    printf("Total de sapos: %d\n", S);
    printf("Percentual de coelhos: %.2f %%\n", 100.0*C/(double)total);
    printf("Percentual de ratos: %.2f %%\n", 100.0*R/(double)total);
    printf("Percentual de sapos: %.2f %%\n", 100.0*S/(double)total);
    return 0;
}
