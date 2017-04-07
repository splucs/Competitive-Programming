#include <cstdio>

int main()
{
    int N, L, R;
    while(true){
        scanf("%d", &N);
        if (N==0) break;
        for(int i=0; i<N; i++){
            R=0;
            for(int j=1; j<=5; j++){
                scanf("%d", &L);
                if (R==0 && L<=127) R=j;
                else if (L<=127) R=6;
            }
            if (R>=1 && R<=5) printf("%c\n", 'A'-1+R);
            else printf("*\n");
        }
    }
    return 0;
}
