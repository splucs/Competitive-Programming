#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 200009
#define MOD 1000000007
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;

ll extGcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1; y = 0; return a;
	}
	else {
		ll g = extGcd(b, a%b, y, x);
		y -= a/b * x; return g;
	}
}

ll modExp(ll a, ll b, ll mod) {
	ll ans = 1;
	while (b > 0) {
		if (b&1) { ans = (ans*1ll*a) % mod; }
		a = a*1ll*a % mod;
		b >>= 1;
	}
	return ans;
}

ll modInv(ll a, ll m) {
	return modExp(a, m-2, m);
}

ll modDiv(ll a, ll b, ll m) {
	return ((a%m)*modInv(b, m)) % m;
}

ll fat[MAXN], inv[MAXN];
void preprocessfat() {
	fat[0] = 1;
	inv[0] = 1;
	FOR1(i, MAXN-1) {
		fat[i] = (i*fat[i-1])%MOD;
		inv[i] = modExp(fat[i], MOD-2, MOD);
	}
}

ll pascal(ll n, ll k) {
	return (fat[n]*inv[k])%MOD*inv[n-k]%MOD;
}

int n, x[MAXN], y[MAXN], r, c;
ii blocks[MAXN];

int dp[MAXN][2];

int main() {
	preprocessfat();
	int T;
	scanf("%d", &T);
	FOR1(t, T) {
		scanf("%d %d %d", &r, &c, &n);
		FOR1(i, n) scanf("%d %d", &blocks[i].fi, &blocks[i].se);
		sort(blocks+1, blocks+1+n);
		FOR1(i, n) {
			x[i] = blocks[i].fi;
			y[i] = blocks[i].se;
		}
		mset(dp, -1);
		int dx = r-1;
		int dy = c-1;
		int ans = pascal(dx+dy, dx);
		REP1(u, n) FOR(p, 2) {
			dx = r - x[u];
			dy = c - y[u];
			dp[u][p] = (p*pascal(dx+dy, dx))%MOD;
			for(int v = u+1; v <= n; v++) {
				dx = x[v] - x[u];
				dy = y[v] - y[u];
				if (u == v || dx < 0 || dy < 0) continue;
				dp[u][p] = (dp[u][p]+(pascal(dx+dy, dx)*dp[v][1-p])%MOD)%MOD;
			}
			dx = x[u]-1;
			dy = y[u]-1;
			if (p == 0) ans = (ans + (dp[u][p]*pascal(dx+dy, dx))%MOD)%MOD;
			else ans = (ans + MOD - (dp[u][p]*pascal(dx+dy, dx))%MOD)%MOD;
		}
		printf("%d\n", ans);
	}
	return 0;
}