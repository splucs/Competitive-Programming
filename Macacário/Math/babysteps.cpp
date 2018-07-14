#include <map>
#include <cmath>
using namespace std;

/*
 * Baby Steps Algorithm for Discrete Logarithm
 */

template <typename T>
T baby (T a, T b, T m) {
	a %= m; b %= m;
	T n = (T) sqrt (m + .0) + 1, an = 1;
	for (T i=0; i<n; ++i) an = (an * a) % m;
	map<T, T> vals;
	for (T i=1, cur=an; i<=n; ++i) {
		if (!vals.count(cur)) vals[cur] = i;
		cur = (cur * an) % m;
	}
	for (T i=0, cur=b; i<=n; ++i) {
		if (vals.count(cur)) {
			T ans = vals[cur] * n - i;
			if (ans < m) return ans;
		}
		cur = (cur * a) % m;
	}
	return -1;
}

/*
 * HackerEarth Dexter plays with GP
 */

#include <cstdio>
typedef long long ll;

int main() {
	int T;
	ll r, x, p, a, b;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%lld %lld %lld", &r, &x, &p);
		a = r;
		b = x*(r-1) + 1;
		printf("%lld\n", baby(a, b, p));
	}
	return 0;
}