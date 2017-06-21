#include <cstdio>
int main(){
    int dt=0, d, h, m, s;
    scanf("Dia %d\n%d : %d : %d\n", &d, &h, &m, &s);
    dt-=s;
    dt-=m*60;
    dt-=h*3600;
    dt-=d*86400;
    scanf("Dia %d\n%d : %d : %d", &d, &h, &m, &s);
    dt+=s;
    dt+=m*60;
    dt+=h*3600;
    dt+=d*86400;
    printf("%d dia(s)\n%d hora(s)\n%d minuto(s)\n%d segundo(s)\n", dt/86400, (dt%86400)/3600, (dt%3600)/60, dt%60);
    return 0;
}
