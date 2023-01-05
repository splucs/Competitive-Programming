#include <bits/stdc++.h>
using namespace std;
#define MAXN 4009
#define MAXLOGN 20
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int M;
int f[MAXN], p[MAXN], k;

vi convolute(const vi &a, const vi &b) {
	vi c(a.size() + b.size() - 1);
	FOR(i, sz(a)) FOR(j, sz(b)) {
		c[i+j] = (c[i+j] + (a[i]*1ll*b[j])) % M;
	}
	return c;
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d %d", &k, &M);
		f[1] = 1%M;
		f[2] = 2%M;
		for(int i = 3; i <= k; i++) f[i] = (f[i-1] + f[i-2])%M;
		FOR1(i, k) {
			scanf("%d", &p[i]);
			p[i] %= M;
			//printf("p(%d) = %d\n", i, p[i]);
		}
		
		vi b; b.pb(1);
		FOR1(i, k) {
			vi cur;
			cur.pb(M-f[i]);
			cur.pb(1);
			b = convolute(b, cur);
		}
		//printf("size b = %d\n", sz(b));
		assert(sz(b) == k+1 && b[k] == 1);
		int ans = 0;
		FOR(i, k) {
			ans = (ans + M - (b[i]*1ll*p[i+1])%M)%M;
		}
		printf("%d\n", ans);
	}
	return 0;
}