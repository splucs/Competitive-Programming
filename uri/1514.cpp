#include <stdio.h>

int main(){
    while (true){
        int N, M;
        scanf ("%d %d", &N, &M);
        if (N==0 && M==0) break;
        int Q[100][100];
        for (int n=0; n<N; n++){
            for (int m=0; m<M; m++){
                scanf ("%d", &Q[n][m]);
            }
        }
        int car1=1, car2=1, car3=1, car4=1;
        bool genio = false;
        for (int n=0; n<N && !genio; n++){
            genio = true;
            for (int m=0; m<M; m++){
                if (Q[n][m]==0) genio=false;
            }
            if (genio) car1=0;
        }
        genio=false;
        for (int m=0; m<M && !genio; m++){
            genio = true;
            for (int n=0; n<N; n++){
                if (Q[n][m]==1) genio=false;
            }
            if (genio) car2=0;
        }
        genio=false;
        for (int m=0; m<M && !genio; m++){
            genio = true;
            for (int n=0; n<N; n++){
                if (Q[n][m]==0) genio=false;
            }
            if (genio) car3=0;
        }
        genio=false;
        for (int n=0; n<N && !genio; n++){
            genio = true;
            for (int m=0; m<M; m++){
                if (Q[n][m]==1) genio=false;
            }
            if (genio) car4=0;
        }
        printf ("%d\n", car1 + car2 + car3 + car4);
    }
    return 0;
}
