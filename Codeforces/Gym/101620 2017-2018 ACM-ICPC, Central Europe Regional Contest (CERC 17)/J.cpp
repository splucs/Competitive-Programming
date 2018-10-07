#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define INF 0x3f3f3f3f
#define MAXN 1000009
#define MAXM 29
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;

vi divide(int a) {
	vi ans;
	for(int i = 1; i*1ll*i <= a; i++) {
		if (a%i == 0) {
			ans.pb(i);
			if (i != a/i) ans.pb(a/i);
		}
	}
	sort(all(ans));
	return ans;
}

int n, size[MAXN];
vi g[MAXN];

int dfs(int u, int p) {
	size[u] = 1;
	for(int v : g[u]) {
		if (v == p) continue;
		size[u] += dfs(v, u);
	}
	//printf("size[%d] = %d\n", u, size[u]);
	return size[u];
}

int main() {
	while(scanf("%d", &n) != EOF) {
		vi divn = divide(n);
		vi cnt(divn.size());
		FOR1(u, n) g[u].clear();
		FOR(j, n-1) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		dfs(1, -1);
		FOR1(u, n) FOR(i, sz(divn)) {
			if (size[u]%divn[i] == 0) cnt[i]++;
		}
		REP(i, sz(cnt)) {
			//printf("cnt[%d] = %d\n", divn[i], cnt[i]);
			if (cnt[i] > 1 && n/divn[i] == cnt[i]) printf("%d ", cnt[i]-1);
		}
		printf("\n");
	}
	return 0;
}