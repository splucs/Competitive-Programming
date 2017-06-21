#include <cstdio>
int N, M;
int mat[59][59];
bool visiting[59][59];

int visit(int a, int b, int h){
    if (h==1) return mat[a][b];
    visiting[a][b]=true;
    int maxvalor = -1, x = -1;
    if (a>0 && !visiting[a-1][b]){
        x = visit(a-1, b, h-1);
        if (maxvalor<x) maxvalor = x;
    }
    if (b>0 && !visiting[a][b-1]) {
        x = visit(a, b-1, h-1);
        if (maxvalor<x) maxvalor = x;
    }
    if (a+1<N && !visiting[a+1][b]){
        x = visit(a+1, b, h-1);
        if (maxvalor<x) maxvalor = x;
    }
    if (b+1<N && !visiting[a][b+1]){
        x = visit(a, b+1, h-1);
        if (maxvalor<x) maxvalor = x;
    }
    visiting[a][b]=false;
    if(maxvalor<0) return -1;
    return maxvalor + mat[a][b];
}

int main()
{
    scanf("%d %d", &N, &M);
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            visiting[i][j]=false;
            scanf("%d", &mat[i][j]);
        }
    }
    int maxvalor=-1, x;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            x = visit(i, j, M);
            if(maxvalor<x) maxvalor = x;
        }
    }
    printf("%d\n", maxvalor);
    return 0;
}
