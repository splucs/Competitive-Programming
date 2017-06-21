#include <cstdio>
int main()
{
    int h1, h2, m1, m2;
    scanf("%d %d %d %d", &h1, &m1, &h2, &m2);
    m2+=h2*60;
    m1+=h1*60;
    if (m1>m2) m2+=24*60;
    printf("O JOGO DUROU %d HORA(S) E %d MINUTO(S)\n", (m2-m1)/60, (m2-m1)%60);
    return 0;
}
