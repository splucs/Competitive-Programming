/*
             /\\
              .\\\..
              \\   \\
              \ (o) /
              (/    \
               /\    \
              ///     \
             ///|     |
            ////|     |
           //////    /
           |////    /
          /|////--V/  Stephen Morgana
         //\//|   |
     ___////__\___\__________
    ()_________'___'_________)
        \\\\
          \\\
            \\
*/

#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 409
#define MAXM 21
#define MOD 1000000000000000007
#define INF 0x3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

char field[MAXN][MAXN], sup[MAXN][MAXN];
int R, C;

bool allowed[MAXM][MAXM], vis[MAXM][MAXM];
int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

int dfs(int i, int j) {
	if (vis[i][j] || !allowed[i][j]) return 0;
	vis[i][j] = true;
	FOR(k, 4) {
		int ni = i+di[k];
		int nj = j+dj[k];
	}
}

map<ll, int> used;
int qi[MAXN], qj[MAXN];

int match(int si, int sj) {
	int ans = 0;
	mset(allowed, false);
	mset(vis, false);
	ll hsh = 0;
	FOR(it, R) {
		if(sup[si+it][sj] == 'B') break;
		hsh++;
	}
	hsh *= 21;
	FOR(jt, C) {
		if(sup[si][sj+jt] == 'B') break;
		hsh++;
	}
	hsh *= 21;
	REP(it, R) {
		if(sup[si+it][sj] == 'B') break;
		hsh++;
	}
	hsh *= 21;
	REP(jt, C) {
		if(sup[si][sj+jt] == 'B') break;
		hsh++;
	}
	hsh *= 21;
	FOR(it, R) {
		if(sup[si+it][sj+C-1] == 'B') break;
		hsh++;
	}
	hsh *= 21;
	FOR(jt, C) {
		if(sup[si+R-1][sj+jt] == 'B') break;
		hsh++;
	}
	hsh *= 21;
	REP(it, R) {
		if(sup[si+it][sj+C-1] == 'B') break;
		hsh++;
	}
	hsh *= 21;
	REP(jt, C) {
		if(sup[si+R-1][sj+jt] == 'B') break;
		hsh++;
	}
	if(used.count(hsh)) return used[hsh];
	FOR(it, R) FOR(jt, C) {
		if (field[it][jt] == sup[si+it][sj+jt]) {
			allowed[it][jt] = true;
		}
	}
	FOR(it, R) FOR(jt, C) {
		if (!vis[it][jt] && allowed[it][jt]) {
			int fr = 0, bk = 0;
			qi[bk] = it;
			qj[bk] = jt;
			bk++;
			int cur = 0;
			vis[it][jt] = true;
			while(bk > fr) {
				cur++;
				int i = qi[fr];
				int j = qj[fr];
				fr++;
				FOR(k, 4) {
					int ni = i+di[k];
					int nj = j+dj[k];
					if (ni < 0 || nj < 0 || ni >= R || nj >= C) continue;
					if (!vis[ni][nj] && allowed[ni][nj]) {
						vis[ni][nj] = true;
						qi[bk] = ni;
						qj[bk] = nj;
						bk++;
					}
				}
			}
			if (cur > ans) ans = cur;
		}
	}
	return used[hsh] = ans;
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d %d", &R, &C);
		used.clear();
		FOR(i, R) {
			scanf(" %s", field[i]);
			FOR(j, C) {
				FOR(it, R) FOR(jt, C) {
					sup[i*R + it][j*C + jt] = field[i][j];
				}
			}
		}
		int ans = 0;
		FOR(i, R*R) FOR(j, C*C) {
			if (i+R-1 >= R*R) continue;
			if (j+C-1 >= C*C) continue;
			ans = max(ans, match(i, j));
		}
		printf("Case #%d: %d\n", caseNo, ans);
	}
	return 0;
}