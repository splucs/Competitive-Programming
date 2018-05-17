#include <bits/stdc++.h>
using namespace std;
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 300309
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define ROF(x,n) for(int x=(n)-1; (x)>=0; (x)--)
#define ROF1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&(x), (y), sizeof(x));
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;

vi g[MAXN];
int n, x, y, size[MAXN];
bool hasy[MAXN];
ll ans = 0;

void dfs(int u, int p) {
	size[u] = 1;
	hasy[u] = (u == y);
	for(int v : g[u]) {
		if (v == p) continue;
		dfs(v, u);
		if (hasy[v]) hasy[u] = true;
		size[u] += size[v];
	}
}

int main() {
	scanf("%d %d %d", &n, &x, &y);
	FOR(j, n-1) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(x, -1);
	int cnt = 1;
	for(int v : g[x]) {
		if (!hasy[v]) cnt += size[v];
	}
	ll ans = n*1ll*(n-1) - cnt*1ll*size[y];
	printf("%I64d\n", ans);
	return 0;
}