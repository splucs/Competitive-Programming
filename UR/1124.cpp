#include <cstdio>

int main(){
    int L, C, R1, R2;
    while(true){
        scanf("%d %d %d %d", &L, &C, &R1, &R2);
        if (L==0 && C==0 && R1==0 && R2==0) break;
        if (R1*2 > L || R1*2 > C || R2*2 > L || R2*2 > C) printf("N\n");
        else if ((L-R2-R1)*(L-R2-R1) + (C-R2-R1)*(C-R2-R1) >= (R1+R2)*(R1+R2)) printf("S\n");
        else printf("N\n");
    }
    return 0;
}
