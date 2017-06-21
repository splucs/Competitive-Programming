#include <cstdio>
int main()
{
    for (int i=1, j=60; j>=0; j-=5, i+=3) printf("I=%d J=%d\n", i, j);
    return 0;
}
