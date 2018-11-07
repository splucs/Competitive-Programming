#include <bits/stdc++.h>
#define MAXN 100009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define all(x) x.begin(), x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef vector<int> vi;

int par[MAXN];

int find(int i) {
	if (par[i] == i) return i;
	return par[i] = find(par[i]);
}

bool isSameSet(int i, int j) {
	return find(i) == find(j);
}

void unite(int i, int j) {
	par[find(i)] = find(j);
}

vector<int> col[MAXN];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	FOR1(i, n) {
		par[i] = i;
		int k;
		scanf("%d", &k);
		while(k --> 0) {
			int j;
			scanf("%d", &j);
			col[j].pb(i);
		}
	}
	int ans = 0;
	FOR1(j, m) {
		assert(col[j].size() == 2u);
		int u = col[j][0];
		int v = col[j][1];
		if (!isSameSet(u, v)) {
			unite(u, v);
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}