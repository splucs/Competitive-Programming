#include <cstdio>
int main()
{
    int N, counter=0, x;
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%d", &x);
        if (x>=10 && x<=20) counter++;
    }
    printf("%d in\n%d out\n", counter, N-counter);
    return 0;
}
