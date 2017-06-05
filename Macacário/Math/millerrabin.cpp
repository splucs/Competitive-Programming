#include <cstdio>
#include <cmath>

typedef long long ll;

template<typename T>
T modExp(T a, T b, T m) {
    if (b == 0) return 1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c *= a;
    return c;
}

bool mrtest (ll a, ll s, ll d, ll n){
    ll x = modExp(a, d, n);
    if (x == 1 || x == n-1) return true;
    for (; s > 0 ;s--)
        if ((x = (x * x) % n) == n-1) return true;
    return false;
}

// Teste de primalidade de Miller-Rabin, bizu para números gigantes
// Garantido p/ n < 4,759,123,141,  a = 2, 7, and 61 (unsigned int)
// Melhor que o teste normal para n > 100,000
bool millerrabin(ll n){
    ll s, d;
    if (n < 5 || n % 2 == 0 || n % 3 == 0)
        return (n == 2 || n == 3);
    for (s = 0, d = n-1; d % 2 == 0; s++, d /= 2);
    return  mrtest (2, s, d, n) &&
               (n <= 7 || mrtest (7, s, d, n)) &&
               (n <= 61 || mrtest (61, s, d, n));
}

int main(){
    for(int i=1; i<100; i++){
        if (millerrabin(i)) printf("%d is prime\n", i);
        else printf("%d is not prime\n", i);
    }
    return 0;
}
