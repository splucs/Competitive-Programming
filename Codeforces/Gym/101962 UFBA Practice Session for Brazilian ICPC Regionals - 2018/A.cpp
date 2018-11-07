#include <bits/stdc++.h>
#define MAXN 200009
#define MAXM 100009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

ll getGeneratorOutput(ll M, ll a, ll b, ll x, ll input) {
	a = __gcd(a, M);
	b %= a;
	if (x < b) return input;
	x++;
	ll ans = (x-b)/a;
	if ((x-b)%a != 0) ans++;
	if (ans > M/a) ans = M/a;
	return min(INFLL, ans + input);
}

ll getSourceOutput(vector<ll> &arr, ll x, ll input) {
	int lo = -1;
	int hi = sz(arr);
	while(hi > lo+1) {
		int mid = (hi + lo) / 2;
		if (arr[mid] <= x) lo = mid;
		else hi = mid;
	}
	return min(INFLL, hi + input);
}

ll getSelectOutput(ll k1, ll k2, ll input) {
	ll ans = input;
	ans -= k1-1;
	if (ans < 0) ans = 0;
	if (ans > k2-k1+1) ans = k2-k1+1;
	return ans;
}

bool getPrintOutput(ll k, ll input) {
	return input >= k;
}

const int SOURCE = 1;
const int SELECT = 2;
const int GENERATOR = 3;
const int PRINT = 4;

int n, m;
vector<int> g[MAXN];
int type[MAXN];

ll a[MAXN], b[MAXN], M[MAXN];
vector<ll> arr[MAXN];
ll k1[MAXN], k2[MAXN];
ll k[MAXN];

int deg[MAXN], q[MAXN];
ll input[MAXN];

bool kahn(ll x) {
	FOR1(u, n) deg[u] = input[u] = 0; 
	FOR1(u, n) for(int v : g[u]) deg[v]++;
	int en = 0;
	FOR1(u, n) {
		if (deg[u] == 0) q[en++] = u;
	}
	FOR(st, en) {
		int u = q[st];
		ll output;

		if (type[u] == SOURCE) {
			output = getSourceOutput(arr[u], x, input[u]);
		}
		if (type[u] == SELECT) {
			output = getSelectOutput(k1[u], k2[u], input[u]);
		}
		if (type[u] == GENERATOR) {
			output = getGeneratorOutput(M[u], a[u], b[u], x, input[u]);
		}
		if (type[u] == PRINT) {
			return getPrintOutput(k[u], input[u]);
		}

		for(int v : g[u]) {
			deg[v]--;
			input[v] += output;
			input[v] = min(input[v], INFLL);
			if (deg[v] == 0) q[en++] = v;
		}
	}
	assert(false);
}

int main() {
	scanf("%d %d", &n, &m);
	FOR1(u, n) {
		char str[10];
		scanf(" %s", str);
		if (!strcmp(str, "source")) {
			type[u] = SOURCE;
			int k;
			scanf("%d", &k);
			FOR(i, k) {
				ll x;
				scanf("%lld", &x);
				arr[u].pb(x);
			}
			sort(all(arr[u]));
		}
		if (!strcmp(str, "print")) {
			type[u] = PRINT;
			scanf("%lld", &k[u]);
		}
		if (!strcmp(str, "select")) {
			type[u] = SELECT;
			scanf("%lld %lld", &k1[u], &k2[u]);
		}
		if (!strcmp(str, "generator")) {
			type[u] = GENERATOR;
			scanf("%lld %lld %lld", &a[u], &b[u], &M[u]);
		}
	}
	FOR(j, m) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
	}

	ll lo = -1;
	ll hi = INFLL;
	while(hi > lo + 1) {
		ll x = (hi + lo) / 2;
		if (kahn(x)) hi = x;
		else lo = x;
	}
	if (hi == INFLL) hi = -1;
	printf("%lld\n", hi);
	
	return 0;
}