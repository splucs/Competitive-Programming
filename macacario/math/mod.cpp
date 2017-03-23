#include <cstdio>
#define MAXN 1000009
#define REM 1000000007LL

template <typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template <typename T>
T lcm(T a, T b) {
    return a * (b / gcd(a, b));
}

template <typename T>
T extGcd(T a, T b, T& x, T& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    else {
        T g = extGcd(b, a % b, y, x);
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
T modDiv(T a, T b, T m) {
    return ((a % m) * modInv(b, m)) % m;
}

template<typename T>
T modExp(T a, T b, T m) {
    if (b == 0) return 1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c *= a;
    return c;
}

template<typename T>
void diophantine(T a, T b, T c, T& x, T& y) {
    T d = extGcd(a, b, x, y);
    x *= c / d;
    y *= c / d;
}

template<typename T>
T chineseremtheorem(T* a, T* p, int n) {
    T P = 1;
    for(int i=0; i<n; i++) P *= p[i];
    T x = 0, pp;
    for(int i=0; i<n; i++){
        pp = P / p[i];
        x += (a[i]*pp*modInv(pp, p[i])) % P;
    }
    return x % P;
}

ll fat[MAXN];
void preprocessfat(){
    fat[0] = 1;
    for(ll i=1; i<MAXN; i++){
        fat[i] = (i*fat[i-1])%REM;
    }
}

template<typename T>
T pascal(int n, int k, T m){
    return modDiv(fat[n], (fat[k]*fat[n-k])%m, m);
}

int main(void)
{
    int num[] = {3, 4, 5};
    int rem[] = {2, 3, 1};
    int k = sizeof(num)/sizeof(num[0]);
    printf("x = %d\n", chineseremtheorem(rem, num, k));
    return 0;
}