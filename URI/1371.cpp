#include <stdio.h>
#include <math.h>

int main ()
{
    int N;
    scanf("%d", &N);
    while (N)
    {
        for (int i=1; i*i <=N; i++)
        {
            if ((i+1)*(i+1) > N) printf ("%d", i*i);
            else printf ("%d ", i*i);
        }
        printf ("\n");
        scanf("%d", &N);
    }
    return 0;
}
