#include <cstdio>
int main()
{
    int N, x;
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%d", &x);
        if (x==0) {
            printf("NULL\n");
            continue;
        }
        if (x%2==0) printf("EVEN ");
        else printf("ODD ");
        if (x>0) printf("POSITIVE\n");
        else printf("NEGATIVE\n");
    }
    return 0;
}
