#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM 320
#define MOD 1000000007LL
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

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

template<typename T>
T modExp(T a, T b, T m) {
    if (b == 0) return (T)1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c = (c*a) % m;
    return c;
}

typedef long long ll;
ll fat[MAXN];

void preprocessfat() {
	fat[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		fat[i] = (i*fat[i-1])%MOD;
	}
}

ll pascal(int n, int k) {
	ll ans = fat[n] * modInv(fat[k] * fat[n-k] % MOD, MOD) % MOD;
	return ans;
}

ll stirling(int n, int k) {
	ll ans = 0, m1 = k % 2 == 0 ? 1 : -1;
	for(int j = 0; j <= k; j++) {
		ans += m1*(pascal(k, j)*modExp(ll(j), ll(n), MOD)%MOD);
		ans = (ans + MOD) % MOD;
		m1 = -m1;
	}
	ans = (ans*modInv(fat[k], MOD)) % MOD;
	return ans;
}

ll solve(int n, int k) {
	return (stirling(n, k) + (n-1)*stirling(n-1, k))%MOD;
}

int main() {
	preprocessfat();
	int n, k;
	ll sum = 0;
	scanf("%d %d", &n, &k);
	FOR(i, n) {
		ll x;
		scanf("%I64d", &x);
		sum = (sum + x) % MOD;
	}
	ll ans = (sum*solve(n, k)) % MOD;
	printf("%I64d\n", ans);
	return 0;
}