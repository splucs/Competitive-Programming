#include <cstdio>
int main()
{
    int maior=0, pos=1, x;
    for (int i=1; i<=100; i++){
        scanf("%d", &x);
        if (x>maior){
            maior = x;
            pos=i;
        }
    }
    printf("%d\n%d\n", maior, pos);
    return 0;
}
