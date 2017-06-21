/*
    Quebrando um pouquinho a cabeça, podemos ver que a resposta é
    C(N+C-1, C)%REM, C(n, k) é a combinação de n elementos k a k.

    C(n, k) = n!/((n-k)!*k!)

    Assim, basta calcular todos os fatoriais resto REM até o máximo (O(n))
    e calcular (n!/((n-k)!*k!)) % REM.

    Pra isso usamos a propriedade:
    (a / b) mod p = ((a mod p) * (b^(-1) mod p)) mod p,
    em que b^(-1) mod p é o inverso modular de b módulo p
    Pra calcular o inverso modular basta usar o algoritmo de euclides extendido.
*/

#include <cstdio>
#define MAXN 2000009
#define REM 1300031LL

typedef long long int ll;
ll fat[MAXN];

template <typename T>
T extGcd(T a, T b, T& x, T& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    else {
        int g = extGcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}
 
template <typename T>
T modInv(T a, T m) {
    T x, y;
    extGcd(a, m, x, y);
    return (x % m + m) % m;
}
 
template <typename T>
T divMod(T a, T b, T m) {
    return ((a % m) * modInv(b, m)) % m;
}

int main()
{
    fat[0] = 1;
    for(ll i=1; i<MAXN; i++){
        fat[i] = (i*fat[i-1])%REM;
    }

    int T, N, C;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &N, &C);
        printf("%lld\n", divMod(fat[N+C-1], (fat[C]*fat[N-1])%REM, REM));
    }
    return 0;
}