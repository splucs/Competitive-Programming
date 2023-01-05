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
#define MAXN 109
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

int bot[MAXN], b[MAXN], C;
char field[MAXN][MAXN];

bool check(int n) {
	mset(field, '.');
	int i = 0, j = 0;
	FOR(i, C) b[i] = bot[i];
	while(j < C) {
		if (b[j] == 0) {
			j++; continue;
		}
		for(int k = i; k < j; k++) {
			if (k-i >= n) return false;
			field[k-i][k] = '\\';
		}
		for(int k = i; k > j; k--) {
			if (i-k >= n) return false;
			field[i-k][k] = '/';
		}
		i++;
		b[j]--;
	}
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d", &C);
		int tot = 0;
		FOR(i, C) {
			scanf("%d", &bot[i]);
			tot += bot[i];
		}
		int lo = -1;
		int hi = MAXN;
		if (tot != C || bot[0] == 0 || bot[C-1] == 0 || !check(hi)) {
			printf("Case #%d: IMPOSSIBLE\n", caseNo);
			continue;
		}
		while(hi > lo + 1) {
			int mid = (hi + lo) / 2;
			if (check(mid)) hi = mid;
			else lo = mid;
		}
		check(hi);
		printf("Case #%d: %d\n", caseNo, hi+1);
		FOR(i, hi) {
			field[i][C] = 0;
			printf("%s\n", field[i]);
		}
		FOR(i, C) printf(".");
		printf("\n");
	}
	return 0;
}