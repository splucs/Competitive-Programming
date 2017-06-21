#include <cstdio>

int main(){
    int A, B, C;
    while(scanf("%d %d %d", &A, &B, &C) != EOF){
        if (A+B+C == 0 || A+B+C == 3) printf("*\n");
        else if (A+B+C==1){
            if (A==1) printf("A\n");
            if (B==1) printf("B\n");
            if (C==1) printf("C\n");
        }
        else if (A+B+C==2){
            if (A==0) printf("A\n");
            if (B==0) printf("B\n");
            if (C==0) printf("C\n");
        }
    }
    return 0;
}
