#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define MOD 998244353LL

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

typedef long long ll;

ll fat[MAXN];
void preprocessfat(){
    fat[0] = 1;
    for(ll i=1; i<MAXN; i++){
        fat[i] = (i*fat[i-1])%MOD;
    }
}

template<typename T>
T pascal(int n, int k, T m){
    return modDiv(fat[n], (fat[k]*fat[n-k])%m, m);
}

int main() {
	preprocessfat();
	ll a, b, c;
	scanf("%I64d %I64d %I64d", &a, &b, &c);
	ll ans = 1, cur;
	cur = 0;
	for(ll k=0; k<=a && k<=b; k++) {
		cur = (cur + pascal(a, k, MOD)*modDiv(fat[b], fat[b-k], MOD)) % MOD;
	}
	ans = (ans*cur) % MOD;
	cur = 0;
	for(ll k=0; k<=b && k<=c; k++) {
		cur = (cur + pascal(b, k, MOD)*modDiv(fat[c], fat[c-k], MOD)) % MOD;
	}
	ans = (ans*cur) % MOD;
	cur = 0;
	for(ll k=0; k<=c && k<=a; k++) {
		cur = (cur + pascal(c, k, MOD)*modDiv(fat[a], fat[a-k], MOD)) % MOD;
	}
	ans = (ans*cur) % MOD;
	printf("%I64d\n", ans);
	return 0;
}