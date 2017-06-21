#include <cstdio>
int main()
{
    int c=0, x;
    for (int i =0; i<5; i++){
        scanf("%d", &x);
        if (x%2==0) c++;
    }
    printf("%d valores pares\n", c);
    return 0;
}
