#include <cstdio>
int main()
{
    for (int i=1; i<=9; i+=2){
        for (int j=6+i; j>=4+i; j--){
            printf("I=%d J=%d\n", i, j);
        }
    }
    return 0;
}
