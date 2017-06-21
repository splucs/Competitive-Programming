#include <stdio.h>
int M[300][300];
void TrocarColuna(int m, int n, int t){
    int aux;
    for (int k=0; k<t; k++){
        aux=M[k][m];
        M[k][m]=M[k][n];
        M[k][n]=aux;
    }
}
void TrocarLinha(int m, int n, int t){
    int aux;
    for (int k=0; k<t; k++){
        aux=M[m][k];
        M[m][k]=M[n][k];
        M[n][k]=aux;
    }
}
int main (){
    while (true){
        int L, N, trocas=0;
        if (!scanf ("%d %d", &L, &N))
            break;
     //   printf ("L=%d N=%d\n", L, N);
        int aux, x, y;
        for (int i=0; i<L; i++){
            for (int j=0; j<N; j++){
                scanf ("%d", &M[i][j]);
                if (M[i][j]==1)
                    x=i, y=j;
            }
        }
        if (x!=0){
          //  printf ("loop linha 1 executado\n");
            TrocarLinha(0, x, N);
            trocas++;
        }
        if (y!=0){
          //  printf ("loop coluna 1 executado\n");
            TrocarColuna(0, y, L);
            trocas++;
        }
        for (int i=0; i<N; i++){
            if (M[0][i]!=i+1){
              //  printf ("\nloop coluna executado\n");
                trocas++;
                TrocarColuna(i, M[0][i]-1, L);
                for (int m=0; m<L; m++){
                //    printf ("\n");
                    for (int n=0; n<N; n++){
                   //     printf ("%d ", M[m][n]);
                    }
                }
            }
        }
        for (int i=0; i<L; i++){
            if (M[i][0]!=1+i*N){
             //   printf ("\nloop linha executado\n");
                trocas++;
                TrocarLinha(i, (M[i][0]-1)/N, N);
                for (int m=0; m<L; m++){
                 //   printf ("\n");
                    for (int n=0; n<N; n++){
                    //    printf ("%d ", M[m][n]);
                    }
                }
            }
        }
        bool igual=true;
        int contador=1;
        for (int i=0; i<L; i++){
        //    printf ("\n");
            for (int j=0; j<N; j++){
                if (M[i][j]!=contador)
                    igual=false;
                contador++;
             //   printf ("%d ", contador);
            }
        }
        if (igual)
            printf ("%d\n", trocas);
        else printf ("*\n");
    }
    return 0;
}
