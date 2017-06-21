#include <cstdio>

int main()
{
    int G, P, S, K, x, y, maxK, maxP;
    int X[100][100];
    int M[100][100];
    int Y[100][100];
    bool first;
    while(true){
        scanf("%d %d", &G, &P);
        if (G==0 && P==0) break;
        for (int i=0; i<P; i++){
            for (int j=0; j<100; j++){
                X[j][i]=0;
            }
        }
        for (int i=0; i<G; i++){
            for (int j=0; j<P; j++){
                scanf("%d", &x);
                X[x-1][j]++;
            }
        }
        scanf("%d", &S);
        maxK=0;
        for (int i=0; i<S; i++){
            scanf("%d", &K);
            if (maxK<K) maxK=K;
            for (x=0; x<K; x++){
                scanf("%d", &M[i][x]);
            }
            while (x<100) M[i][x++]=0;
        }
        for(int i=0; i<S; i++){
            for (int j=0; j<P; j++){
                Y[i][j]=0;
                for (int k=0; k<maxK; k++){
                    Y[i][j]+= M[i][k]*X[k][j];
                }
            }
        }
        for(int i=0; i<S; i++){
            maxP=0;
            for (int j=0; j<P; j++){
                if (Y[i][j]>maxP) maxP = Y[i][j];
            }
            first = true;
            for (int j=0; j<P; j++){
                if (Y[i][j]==maxP && first){
                    printf("%d", j+1);
                    first = false;
                }
                else if (Y[i][j]==maxP){
                    printf(" %d", j+1);
                }
            }
            printf("\n");
        }
    }
    return 0;
}
