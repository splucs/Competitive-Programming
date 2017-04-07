#include <cstdio>

int main()
{
    int N[10], V;
    scanf("%d", &V);
    N[0]=V;
    for (int i = 1; i < 10; ++i)
    {
    	N[i]=2*N[i-1];
    }
    for (int i = 0; i < 10; ++i)
    {
    	printf("N[%d] = %d\n", i, N[i]);
    }
    return 0;
}
