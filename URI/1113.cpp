#include <cstdio>

int main()
{
    int x, y;
    while (scanf("%d %d", &x, &y)!=EOF){
        if (x>y) printf("Decrescente\n");
        if (x<y) printf("Crescente\n");
    }
    return 0;
}
