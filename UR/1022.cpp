#include <cstdio>
int mdc(int x, int y)
{
    int r;
    r = x%y;
    if (r==0) return y;
    else return mdc(y, r);
}
int main()
{
    int N;
    scanf("%d", &N);
    int N1, N2, N3, D1, D2, D3, N4, D4, m;
    char op;
    while (N-->0)
    {
        scanf("%d / %d %c %d / %d", &N1, &D1, &op, &N2, &D2);
        switch(op)
        {
            case '+':
                N3= (N1*D2 + N2*D1);
                D3= D1*D2;
                break;
            case '-':
                N3= (N1*D2 - N2*D1);
                D3= D1*D2;
                break;
            case '*':
                N3 = N1*N2;
                D3 = D1*D2;
                break;
            case '/':
                N3 = N1*D2;
                D3 = N2*D1;
                break;
            default: break;
        }
        m = mdc(N3, D3);
        N4 = N3/m;
        D4 = D3/m;
        if (D4<0)
        {
            D4*=-1;
            N4*=-1;
        }
        printf("%d/%d = %d/%d\n", N3, D3, N4, D4);
    }
    return 0;
}
