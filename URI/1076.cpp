#include <cstdio>

int main()
{
    int T, N, V, A, x, y;
    scanf ("%d", &T);
    for (int t=0; t<T; t++)
    {
        scanf("%d", &N);
        scanf ("%d %d", &V, &A);
        V=0;
        bool mat[50][50];
        for (int i=0; i<50; i++)
        {
            for (int j=0; j<50; j++)
            {
                mat[i][j]=false;
            }
        }
        for (int i=0; i<A; i++)
        {
            scanf("%d %d", &x, &y);
            if(!mat[x][y])
            {
                mat[x][y] = mat[y][x] = true;
                V+=2;
            }
        }
        printf ("%d\n", V);
    }
    return 0;
}
