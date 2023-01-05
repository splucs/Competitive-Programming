#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define MAXN 109
#define MAXM 1000009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define pb push_back
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x);
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef vector<int> vi;

int pos[10][10], from[MAXN], to[MAXN];
bool edge[MAXN], cur[MAXN], line[10], used[10];
vector<ii> dep[MAXN];

int main() {
	int cnt = 0;
	FOR1(i, 9) FOR1(j, 9) {
		pos[i][j] = ++cnt;
		from[cnt] = i;
		to[cnt] = j;
	}

	dep[pos[1][3]].pb({pos[1][2], pos[2][3]});
	dep[pos[4][6]].pb({pos[4][5], pos[5][6]});
	dep[pos[7][9]].pb({pos[7][8], pos[8][9]});
	
	dep[pos[1][7]].pb({pos[1][4], pos[4][7]});
	dep[pos[2][8]].pb({pos[2][5], pos[5][8]});
	dep[pos[3][9]].pb({pos[3][6], pos[6][9]});

	dep[pos[1][9]].pb({pos[1][5], pos[5][9]});
	dep[pos[3][7]].pb({pos[3][5], pos[5][7]});

	int m;
	while(scanf("%d", &m) != EOF) {
		mset(edge, false);
		mset(line, false);
		FOR(j, m) {
			int u, v;
			scanf("%d %d", &u, &v);
			if (v < u) swap(u, v);
			int e = pos[u][v];
			if (dep[e].empty()) {
				edge[e] = true; line[from[e]] = true; line[to[e]] = true;
			}
			else {
				int e1 = dep[e][0].fi, e2 =  dep[e][0].se;
				edge[e1] = true; line[from[e1]] = true; line[to[e1]] = true;
				edge[e2] = true; line[from[e2]] = true; line[to[e2]] = true;
			}
		}
		int per[10];
		FOR1(i, 9) per[i] = i;
		bool ok = false;
		do {
			mset(cur, false);
			mset(used, false);
			int n;
			used[per[1]] = true;
			for(n = 1; n <= 8; n++) {
				int u = per[n];
				int v = per[n+1];
				used[u] = true;
				if (v < u) swap(u, v);
				int e = pos[u][v];
				if (dep[e].empty()) {
					if (!edge[e]) break;
					else {
						used[v] = true;
						cur[e] = true;
					}
				}
				else {
					int e1 = dep[e][0].fi, e2 =  dep[e][0].se;
					if (!edge[e1] || !edge[e2]) break;
					else {
						used[v] = true;
						cur[e1] = true;
						cur[e2] = true;
					}
				}
			}
			ok = true;
			FOR1(e, cnt) {
				if (edge[e] != cur[e]) ok = false;
			}
			FOR1(i, 9) if (used[i] != line[i]) ok = false;
			if (ok) {
				printf("YES\n");
				FOR1(i, n) printf("%d ", per[i]);
				printf("\n");
				break;
			}
		} while(next_permutation(per+1, per+10));
		if (!ok) printf("NO\n");
	}
	return 0;
}