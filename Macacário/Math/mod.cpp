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
T modMul(T a, T b, T m) {
	T x = 0, y = a % m;
	while (b > 0) {
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
	x *= c / d; y *= c / d;
}

#define MAXN 1000009
typedef long long ll;

ll fat[MAXN];
void preprocessfat(ll m) {
	fat[0] = 1;
	for(ll i=1; i<MAXN; i++) {
		fat[i] = (i*fat[i-1])%m;
	}
}

template<typename T>
T pascal(int n, int k, T m) {
	return modDiv(fat[n], (fat[k]*fat[n-k])%m, m);
}

template<typename T>
void allInv(T inv[], T p) {
	inv[1] = 1;
	for (int i = 2; i < p; i++)
		inv[i] = (p - (p/i)*inv[p%i]%p)%p;
}