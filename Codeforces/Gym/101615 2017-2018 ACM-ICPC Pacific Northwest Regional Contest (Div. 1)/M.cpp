#include <bits/stdc++.h>
#define MAXN 5009
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define REP(x,n) for(int x=n-1; x>=0; x--)
#define REP1(x,n) for(int x=n; x>0; x--)
#define pb push_back
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
typedef vector<int> vi;

const int OFFSET = 2001;

vector<int> adj[MAXN];
int vis[MAXN];

int neg(int val) {
	val -= OFFSET;
	val *= -1;
	val += OFFSET;
	return val;
}

bool marked[MAXN];

bool dfs(int u, int iter, bool flag) {
	bool ans = false;
	vis[u] = iter;
	
	if (flag && u < OFFSET) { // started from a positive and reached negative
		marked[u] = true;
		ans = true;
	} 
	
	FOR(i, sz(adj[u])) {
		int v = adj[u][i];
		if (vis[v] == iter) continue;
		if (dfs(v, iter, flag)) ans = true;
	}
	return ans;
}

int main() {
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	FOR(i, m) {
		scanf("%d %d", &a, &b);
		a += OFFSET; b += OFFSET;
		adj[neg(a)].push_back(b);
		if (a != b) adj[neg(b)].push_back(a);
	}

	int iter = 0, ans = -1;
	for (int i = 1; i <= n; i++) {
		bool maybeLoop = false;
		
		++iter;
		if (dfs(OFFSET + i, iter, true)) marked[OFFSET + i] = true;

		if (vis[OFFSET - i] == iter) {
			ans = 1;
			maybeLoop = true;
		}

		++iter;
		dfs(OFFSET - i, iter, false);
		if (vis[OFFSET + i] == iter && maybeLoop) {
			puts("0");
			return 0;
		}
	}
	if (ans != -1) {
		puts("1");
		return 0;
	}

	for (int i = 1; i <= n; i++) {
		if (marked[OFFSET + i] && marked[OFFSET - i]) {
			puts("2");
			return 0;
		}
	}
	puts("-1");
	return 0;
}