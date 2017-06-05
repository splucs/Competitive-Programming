#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

int mat[21][21];
int R, C, X, M, N, n1, n2;

void dfs(int* cont, int a, int b){
    (*cont)++;
    mat[a][b]=2;
    if (a+1<N && mat[a+1][b]==0) dfs(cont, a+1, b);
    if (b+1<M && mat[a][b+1]==0) dfs(cont, a, b+1);
    if (a-1>0 && mat[a-1][b]==0) dfs(cont, a-1, b);
    if (b-1>0 && mat[a][b-1]==0) dfs(cont, a, b-1);
}

void clean(){
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            if (mat[i][j]==2) mat[i][j]=0;
        }
    }
}

bool track(int baixo, int dir, int a, int b){
    mat[a][b]=1;
    if (baixo==1 && dir==1){
        for (int j=0; j<M; j++){
            for (int i=N-1; i>=0; i--){
                if (mat[i][j]==0){
                    int cont=0;
                    dfs(&cont, i, j);
                    for (int k=0; k<=M-n1; k++){
                        if ((j==0 && (cont+N*k)%X==0) || (j>0 && (cont-N*k)%X==0)){
                            clean();
                            mat[a][b]=0;
                            return false;
                        }
                    }
                    clean();
                    return true;
                }
            }
        }
    }
    else if (baixo>1 && track(baixo-1, dir, a+1, b)) return true;
    else if (dir>1 && track(baixo, dir-1, a, b+1)) return true;
    mat[a][b]=0;
    return false;
}

int main()
{
    int T, aux;
    bool vitoria;
    scanf("%d", &T);
    for (int caso=1; caso<=T; caso++){
        scanf("%d %d %d", &X, &R, &C);
        M = max(R, C);
        N = min(R, C);
        if ((R*C)%X!=0) vitoria=true;
        else if (R>=3 && C>=3 && X>=7) vitoria = true;
        else if (N>=X) vitoria =false;
        else{
            for (int i=0; i<N; i++){
                for (int j=0; j<M; j++){
                    mat[i][j]=0;
                }
            }
            if (M>X){
                n1 = ((X+1)%2!=0? X/2+1:(X+1)/2);
                n2 = (X+1)/2;
                if (n2<N) vitoria = false;
                else if (n2>N) vitoria = true;
                else vitoria = track(N, n1, 0, 0);
            }
            else if (X>M) vitoria = true;
            else{
                n1 = ((X+1)%2!=0? X/2+1:(X+1)/2);
                n2 = (X+1)/2;
                if (n2>N) vitoria = true;
                else{
                    if (n2<N) vitoria = false;
                    else if (n2>N) vitoria = true;
                    else vitoria = track(N, n1, 0, 0);
                }
            }
        }
        if (vitoria) printf("Case #%d: RICHARD", caso);
        else printf("Case #%d: GABRIEL", caso);
        if (caso<T) printf("\n");
    }
}
