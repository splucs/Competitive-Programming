#include <cstdio>
int main()
{
    int a, b;
    int n;
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        scanf("%d %d", &a, &b);
        if (b==0) printf("divisao impossivel\n");
        else printf("%.1f\n", a/(double)b);
    }
    return 0;
}
