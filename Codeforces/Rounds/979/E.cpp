#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 51
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=(n)-1; (x)>=0; (x)--)
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

ll dp[MAXN][MAXN][MAXN][MAXN];
int n, p, c[MAXN];
ll even[MAXN], odd[MAXN], pascal[MAXN][MAXN], p2[MAXN];

void init() {
	p2[0] = 1;
	FOR1(i, MAXN-1) p2[i] = (2*p2[i-1])%MOD;
	FOR(n, MAXN) FOR(k, MAXN) {
		if (k > n) pascal[n][k] = 0;
		else if (k == 0 || k == n) pascal[n][k] = 1;
		else pascal[n][k] = (pascal[n-1][k] + pascal[n-1][k-1]) % MOD;
	}
	FOR(n, MAXN) {
		even[n] = 0;
		odd[n] = 0;
		FOR(k, n+1) {
			if (k % 2 == 0) even[n] = (even[n] + pascal[n][k]) % MOD;
			else odd[n] = (odd[n] + pascal[n][k]) % MOD;
		}
	}
}

int main() {
	init();
	scanf("%d %d", &n, &p);
	FOR1(i, n) scanf("%d", &c[i]);
	ll ans = 0;

	for(int i = 0; i <= n; i++)
	for(int ew = 0; ew <= i; ew++)
	for(int ow = 0; ew+ow <= i; ow++)
	for(int eb = 0; ew+ow+eb <= i; eb++) {
		int ob = i - ew - ow - eb;

		if (i == 0) {
			dp[i][ew][ow][eb] = 1;
			continue;
		}

		dp[i][ew][ow][eb] = 0;
		//node i is white
		if (c[i] == 1 || c[i] == -1) {
			//is odd white
			if (ow > 0) {
				dp[i][ew][ow][eb] += (dp[i-1][ew][ow-1][eb] * p2[ow + ew - 1 + eb] % MOD) * even[ob] % MOD;
				dp[i][ew][ow][eb] %= MOD;
			}
			//is even white
			if (ew > 0) {
				dp[i][ew][ow][eb] += (dp[i-1][ew-1][ow][eb] * p2[ow + ew - 1 + eb] % MOD) * odd[ob] % MOD;
				dp[i][ew][ow][eb] %= MOD;
			}
		}

		//node is black
		if (c[i] == 0 || c[i] == -1) {
			//is odd black
			if (ob > 0) {
				dp[i][ew][ow][eb] += (dp[i-1][ew][ow][eb] * p2[ob + eb - 1 + ew] % MOD) * even[ow] % MOD;
				dp[i][ew][ow][eb] %= MOD;
			}
			//is even black
			if (eb > 0) {
				dp[i][ew][ow][eb] += (dp[i-1][ew][ow][eb-1] * p2[ob + eb - 1 + ew] % MOD) * odd[ow] % MOD;
				dp[i][ew][ow][eb] %= MOD;
			}
		}

		if (i == n && (ob + ow) % 2 == p) ans = (ans + dp[i][ew][ow][eb]) % MOD;
	}
	printf("%lld\n", ans);
	return 0;
}