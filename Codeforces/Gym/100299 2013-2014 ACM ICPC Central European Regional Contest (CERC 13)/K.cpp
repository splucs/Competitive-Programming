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

int g[30][30];
vi cur, ans;

void dfs(int u) {
	cur.push_back(u);
	if (ans.size() < cur.size()) ans = cur;
	if (ans.size() < 39u) {
		FOR(v, 26) {
			if (!g[u][v]) continue;
			//printf("%c->%c\n", u+'a', v+'a');
			dfs(v);
		}
	}
	cur.pop_back();
}

int main() {
	int T, n;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d", &n);
		FOR(i, 26) FOR(j, 26) g[i][j] = 1;
		char str[5];
		FOR(i, n) {
			scanf(" %s", str);
			int u = str[0] - 'a', v = str[1] - 'a';
			g[u][v] = 0;
		}
		ans.clear();
		FOR(u, 26) {
			cur.clear();
			dfs(u);
		}
		n = (1+sz(ans)) / 2;
		if (n > 20) n = 20;
		FOR(i, n) {
			FOR(j, n) printf("%c", ans[i+j] + 'a');
			printf("\n");
		}
	}
	return 0;
}