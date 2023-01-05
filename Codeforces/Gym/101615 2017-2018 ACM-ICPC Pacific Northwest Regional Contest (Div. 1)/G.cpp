#include <bits/stdc++.h>
#define MAXN 5009
#define INF 0x3f3f3f3f
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

vi g[MAXN], l[MAXN], r[MAXN];
int q[MAXN];
bitset<MAXN> vis;

bool bfs(int s, int t, int k) {
	int st = 0, en = 0;
	vis.reset();
	q[en++] = s;
	vis[s] = 1;
	while(en > st) {
		int u = q[st++], v;
		FOR(i, sz(g[u])) {
			v = g[u][i];
			if (k < l[u][i] || k > r[u][i] || vis[v]) continue;
			vis[v] = 1;
			q[en++] = v;
		}
	}
	return vis[t];
}

int main() {
	int n, m, k;
	while(scanf("%d %d %d", &n, &m, &k) != EOF) {
		int s, t;
		scanf("%d %d", &s, &t);
		set<int> cnt;
		FOR1(u, n) {
			g[u].clear();
			l[u].clear();
			r[u].clear();
		}
		FOR(j, m) {
			int u, v, lb, rb;
			scanf("%d %d %d %d", &u, &v, &lb, &rb);
			g[u].pb(v);
			l[u].pb(lb);
			r[u].pb(rb);
			cnt.insert(lb-1);
			cnt.insert(lb);
			cnt.insert(lb+1);
			cnt.insert(rb-1);
			cnt.insert(rb);
			cnt.insert(rb+1);
		}
		int last = 0;
		int ans = 0;
		for(int i : cnt) {
			if (i < 1) continue;
			if (bfs(s, t, i)) {
				ans += i-last;
			}
			last = i;
		}
		printf("%d\n", ans);
	}
	return 0;
}