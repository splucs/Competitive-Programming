#include <cstdio>
typedef struct matrix{
    int mat[100][100];
    int dim;
} matrix;

void printMatrix(matrix a){
    for (int i=0; i<a.dim; i++){
        for (int j=0; j<a.dim; j++){
            printf("%4d ", a.mat[i][j]);
        }
        printf("\n");
    }
}

matrix createMatrix(int N)
{
    matrix a;
    a.dim = N;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            a.mat[i][j]=0;
        }
    }
    return a;
}

matrix multiply(matrix a, matrix b){
    matrix c = createMatrix(a.dim);
    for (int i=0; i<a.dim; i++){
        for (int j=0; j<a.dim; j++){
            for (int k=0; k<a.dim; k++){
                c.mat[i][j]+=(a.mat[i][k]*b.mat[k][j])%10000;
                c.mat[i][j]%=10000;
            }
        }
    }
    return c;
}

matrix exp(matrix a, int expo){
    if (expo==1) return a;
    matrix k = exp(a, expo/2);
    k = multiply(k, k);
    if (expo%2!=0) k =multiply(k, a);
    //printf("a elevado a %d:\n", expo);
   // printMatrix(k);
    return k;
}

int main()
{
    int N, L, S, T, x;
    while(scanf("%d %d", &N, &L)!=EOF){
        scanf("%d %d", &S, &T);
        matrix a = createMatrix(N);
        for (int i=0; i<N; i++){
            for (int j=0; j<4; j++){
                scanf("%d", &x);
                a.mat[i][x-1]++;
            }
        }
        if (L==0 && S==T){
            printf("1\n");
            continue;
        }
        else if (L==0){
            printf("0\n");
            continue;
        }
     //   printf("a:\n");
     //   printMatrix(a);
        a= exp(a, L);
        printf("%d\n", a.mat[S-1][T-1]);
    }
    return 0;
}
