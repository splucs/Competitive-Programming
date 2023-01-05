#include <cstdio>
int main()
{
    int H1, M1, H2, M2;
    while(true){
        scanf("%d %d %d %d", &H1, &M1, &H2, &M2);
        if (H1==0 && H2==0 && M1==0 && M2==0) break;
        M1=M1+H1*60;
        M2=M2+H2*60;
        if (M2<M1) M2+=1440;
        printf("%d\n", M2-M1);
    }
    return 0;
}
