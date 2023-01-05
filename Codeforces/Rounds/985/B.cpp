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
#define MAXN 2009
#define MAXM 900009
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

char lamp[MAXN][MAXN];
int sw[MAXN];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	mset(sw, 0);
	FOR(i, n) {
		scanf(" %s", lamp[i]);
		FOR(j, m) {
			if (lamp[i][j] == '1') sw[j]++;
		}
	}
	bool ok = false;
	FOR(i, n) {
		ok = true;
		FOR(j, m) {
			if (lamp[i][j] == '1' && sw[j] == 1) ok = false;
		}
		if(ok) break;
	}
	if (ok) printf("YES\n");
	else printf("NO\n");
	return 0;
}