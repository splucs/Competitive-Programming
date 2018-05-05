#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

int odd[MAXN], even[MAXN], size[MAXN], dep[MAXN];
ll V[MAXN];
int N;
vector<int> g[MAXN];

void compute(int u, int p) {
	even[u] = 1;
	odd[u] = 0;
	size[u] = 1;
	if (p <= 0) dep[u] = 0;
	else dep[u] = 1 + dep[p];
	for(int v : g[u]) {
		if (v == p) continue;
		compute(v, u);
		even[u] += odd[v];
		odd[u] += even[v];
		size[u] += size[v];
	}
}

ll ans = 0;

void dfs(int u, int p) {

	int ev, od, mul;
	mul = N - size[u] + 1;
	ev = even[u];
	od = odd[u];
	ans = (ans + (ev*(V[u]*mul)%MOD)%MOD)%MOD;
	ans = (ans - (od*(V[u]*mul)%MOD)%MOD + MOD)%MOD;

	mul = size[u];
	ev = (dep[u]%2 == 0 ? even[1] - even[u] + 1 : odd[1] - even[u] + 1);
	od = (dep[u]%2 == 0 ? odd[1] - odd[u] : even[1] - odd[u]);
	ans = (ans + (ev*(V[u]*mul)%MOD)%MOD)%MOD;
	ans = (ans - (od*(V[u]*mul)%MOD)%MOD + MOD)%MOD;
	ans = (ans - V[u] + MOD) % MOD;

	for(int v : g[u]) {
		if (v == p) continue;
		dfs(v, u);

		mul = size[u] - size[v] - 1;
		ev = odd[v];
		od = even[v];
		ans = (ans + (ev*(V[u]*mul)%MOD)%MOD)%MOD;
		ans = (ans - (od*(V[u]*mul)%MOD)%MOD + MOD)%MOD;
	}
}

int main() {
	scanf("%d", &N);
	FOR1(u, N) scanf("%I64d", &V[u]);
	FOR(j, N-1) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v); g[v].pb(u);
	}
	compute(1, -1);
	dfs(1, -1);
	printf("%I64d\n", ans);
	return 0;
}