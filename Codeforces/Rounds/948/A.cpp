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
#define MAXN 509
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
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

char field[MAXN][MAXN];
int n, m;
int di[4] = {0, -1, 0, 1};
int dj[4] = {-1, 0, 1, 0};

int main() {
	scanf("%d %d", &n, &m);
	FOR(i, n) scanf(" %s", field[i]);
	bool ok = true;
	FOR(i, n) FOR(j, m) {
		if (field[i][j] != 'S') continue;
		FOR(k, 4) {
			int ni = i + di[k];
			int nj = j + dj[k];
			if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
				if (field[ni][nj] == 'W') ok = false;
				else if (field[ni][nj] == '.') field[ni][nj] = 'D';
			}
		}
	}
	if (ok) {
		printf("Yes\n");
		FOR(i, n) printf("%s\n", field[i]);
	}
	else printf("No\n");
	return 0;
}