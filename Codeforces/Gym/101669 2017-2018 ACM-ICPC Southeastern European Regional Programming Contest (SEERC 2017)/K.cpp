#include <bits/stdc++.h>
#define MAXN 100009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;


vi g[MAXN];
int s[MAXN], a[MAXN], inv[MAXN], cnt = 0;
int toposort[MAXN];
bool vis[MAXN];

void ts(int i) {
	//printf("i = %d\n", i);
	if (i == 0 || vis[i]) return;
	vis[i] = true;
	sort(all(g[i]));
	for(int j : g[i]) {
		ts(j);
	}
	toposort[++cnt] = i;
}

int main() {
	int n;
	scanf("%d", &n);
	FOR1(i, n) scanf("%d", &a[i]);
	REP1(i, n) {
		int f = a[i];
		g[s[f-1]].pb(i);
		g[i].pb(s[f]);
		s[f] = i;
	}
	FOR1(i, n) ts(i);
	FOR1(i, n) inv[toposort[i]] = i;
	FOR1(i, n) printf("%d ", inv[i]);
	printf("\n");
	return 0;
}
