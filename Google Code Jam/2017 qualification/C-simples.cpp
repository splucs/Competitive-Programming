#include <stdio.h>

void calcPos(long long n, long long k, long long &l, long long &r)
{
    if (k == 1)
    {
        l = (n + 1) / 2 - 1;
        r = n - (n + 1) / 2;
        return;
    }

    // Answer is on the left side (trust me)
    if (n % 2 != k % 2)
    {
        calcPos((n + 1) / 2 - 1, k / 2, l, r);
    }

    // Answer is on the right side
    else
    {
        calcPos(n - (n + 1) / 2, k / 2, l, r);
    }
}

void query()
{
    long long n, k, l, r;
    scanf("%lld %lld", &n, &k);

    calcPos(n, k, l, r);
    if (l > r)
    {
        printf("%lld %lld\n", l, r);
    }
    else
    {
        printf("%lld %lld\n", r, l);
    }
}

int main()
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++)
    {
        printf("Case #%d: ", i + 1);
        query();
    }

    return 0;
}