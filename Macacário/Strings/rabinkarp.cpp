#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;

/*
 * Rabin Karp
 */

class RabinKarp {
	ll m;
	vector<int> pw, hsh;
public:
	RabinKarp() {}
	RabinKarp(char str[], ll p, ll _m) : m(_m) {
		int n = strlen(str);
		pw.resize(n); hsh.resize(n);
		hsh[0] = str[0]; pw[0] = 1;
		for(int i = 1; i < n; i++) {
			hsh[i] = (hsh[i-1] * p + str[i]) % m;
			pw[i] = (pw[i-1] * p) % m;	
		}
	}
	ll hash(int i, int j) {
		ll ans = hsh[j];
		if (i > 0) ans = (ans - ((hsh[i-1]*1ll*pw[j-i+1])%m) + m) % m;
		return ans;
	}
};

/*
 * Codeforces 961F
 */

#include <cstdio>
#define MAXN 1000009
#define P 256
#define M 1000000007

char str[MAXN];
int N, f[MAXN];
RabinKarp rk;

bool check(int l, int r) {
	if (f[l] <= 0) return true;
	if (l+f[l]-1 >= r) return false;
	return rk.hash(l, l+f[l]-1) == rk.hash(r-f[l]+1, r);
}

int main() {
	scanf("%d %s", &N, str);
	rk = RabinKarp(str, P, M);
	int r = N/2;
	int l = (N % 2 == 0 ? r-1 : r);
	int k = l;
	f[l+1] = -1;
	for(; l >= 0; l--, r++) {
		f[l] = f[l+1]+2;
		while(!check(l, r)) f[l]-=2;
	}
	for(int i = 0; i <= k; i++) printf("%d ", f[i]);
	printf("\n");
	return 0;
}
