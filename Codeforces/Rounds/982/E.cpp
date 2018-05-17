/*
             /\\
              .\\\..
              \\   \\
              \ (o) /
              (/    \
               /\    \
              ///     \
             ///|     |
            ////|     |
           //////    /
           |////    /
          /|////--V/  Stephen Morgana
         //\//|   |
     ___////__\___\__________
    ()_________'___'_________)
        \\\\
          \\\
            \\
*/

#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 100309
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

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
T modMul(T a, T b, T m){
	T x = 0, y = a % m;
	while (b > 0){
		if (b % 2 == 1) x = (x + y) % m;
		y = (y * 2) % m;
		b /= 2;
	}
	return x % m;
}

template<typename T>
T modExp(T a, T b, T m) {
    if (b == 0) return (T)1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c = (c*a) % m;
    return c;
}

template<typename T>
void diophantine(T a, T b, T c, T& x, T& y) {
    T d = extGcd(a, b, x, y);
    x *= c / d; x %= b / d;
    y *= c / d; y %= -a / d;
}

ll n, m, x, y, vx, vy;

int main() {
	scanf("%lld %lld %lld %lld %lld %lld", &n, &m, &x, &y, &vx, &vy);
	if (vx != 0 && vy != 0) {
		ll al = n*vy;
		ll bl = -m*vx;
		ll cl = vy*x - y*vx;
		ll g = gcd(abs(al), abs(bl));
		if (cl % g != 0) {
			printf("-1\n");
			return 0;
		}
		ll a0, b0;
		diophantine(al, bl, cl, a0, b0);
		ll t = abs(bl/g*n/vx);
		ll q = (a0*n-x)/vx;
		ll k = (q%t + t)%t;
		ll a = abs((x+k*vx)/n);
		ll b = abs((y+k*vy)/m);
		printf("%lld %lld\n", a % 2 == 0 ? 0 : n, b % 2 == 0 ? 0 : m);
		return 0;
	}
	if (vx == 0) {
		if (x != 0 && x != n) printf("-1\n");
		else printf("%lld %lld\n", x, vy > 0 && y > 0 ? m : 0);
		return 0;
	}
	if (vy == 0) {
		if (y != 0 && y != m) printf("-1\n");
		else printf("%lld %lld\n", vx > 0 && x > 0 ? n : 0, y);
		return 0;
	}
}