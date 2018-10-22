#include <bits/stdc++.h>
#define MAXN 500009
#define INF 0x3f3f3f3f
#define FOR(x, n) for(int x=0; x<n; x++)
#define REP(x, n) for(int x=n-1; x>=0; x--)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define REP1(x, n) for(int x=n; x>0; x--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;

map<string, int> red;
int cnt;
vector<int> g[MAXN];
int mex[MAXN];

int reduce(string str) {
	if (!red.count(str)) {
		red[str] = ++cnt;
		mex[cnt] = -1;
		g[cnt].clear();
	}
	return red[str];
}

int Mex(int u) {
	if (mex[u] >= 0) return mex[u];
	for(int v : g[u]) {
		if (Mex(v) == 0) return mex[u] = 1;
	}	
	return mex[u] = 0;
}

char buffer[MAXN];
bool start[256];

int main() {
	#ifdef ONLINE_JUDGE
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	#endif

	int n;
	while(scanf("%d", &n) != EOF) {
		red.clear(); cnt = 0;
		mset(start, false);
		int st = reduce(string(""));
		FOR(i, n) {
			scanf(" %s", buffer);
			string s(buffer);
			int m = s.size();
			FOR1(j, m) REP(i, j) {
				string sub = s.substr(i, j-i);
				int u = reduce(sub);
				if (i > 0) g[u].pb(reduce(s.substr(i-1, j-i+1)));
				if (j < m) g[u].pb(reduce(s.substr(i, j-i+1)));
				if (j == i+1) {
					g[st].pb(u);
					start[s[i]] = true;
				}
			}
			mex[reduce(s)] = 1;
		}
		int ans = Mex(st);

		if (ans != 0) {
			printf("First\n");
			buffer[1] = 0;
			FOR(c, 256) {
				if (!start[c]) continue;
				string s; s.push_back(c);
				if (Mex(reduce(s)) == 0) printf("%c", c);
			}
			printf("\n");
		}
		else printf("Second\n");
	}
	return 0;
}