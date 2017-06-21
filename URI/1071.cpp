#include <cstdio>
int main()
{
    int x, y, i;
    scanf("%d %d", &x, &y);
    if (x>y){
        i=y;
        y=x;
        x=i;
    }
    i=(x%2==0? x+1:x+2);
    int soma=0;
    for (;i<y; i+=2){
        soma+=i;
    }
    printf("%d\n", soma);
    return 0;
}
