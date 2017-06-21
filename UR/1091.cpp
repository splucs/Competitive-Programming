#include <cstdio>
int main()
{
    int N, M, K, x, y;
    while(true){
        scanf("%d", &K);
        if (K==0) break;
        scanf("%d %d", &N, &M);
        for(int i=0; i<K; i++){
            scanf("%d %d", &x, &y);
            if (x-N==0 || y-M==0) printf("divisa\n");
            else if (x>N && y>M) printf("NE\n");
            else if (x<N && y>M) printf("NO\n");
            else if (x>N && y<M) printf("SE\n");
            else if (x<N && y<M) printf("SO\n");
        }
    }
    return 0;
}
