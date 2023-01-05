#include <cstdio>
int main()
{
    int X1, X2, Y1, Y2;
    while (true){
        scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
        if (X1==0 && X2==0 && Y1==0 && Y2==0) break;
        int dx=X1-X2, dy=Y1-Y2;
        if (dx<0) dx*=-1;
        if (dy<0) dy*=-1;
        if (dx==0 && dy==0) printf("0\n");
        else if (dx==dy || dx==0 || dy==0) printf("1\n");
        else printf("2\n");
    }
    return 0;
}
