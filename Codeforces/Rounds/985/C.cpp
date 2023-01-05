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
#define MAXN 103009
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

int n, k;
ll l;
int a[MAXN];
bool app[MAXN];
vi barrel[MAXN];

int main() {
	scanf("%d %d %lld", &n, &k, &l);
	FOR(i, n*k) {
		scanf("%d", &a[i]);
	}
	sort(a, a+(n*k));
	int x = n*k - 1;
	while(a[x] > a[0] + l) x--;
	if (x+1 < n) {
		printf("0\n");
		return 0;
	}

	mset(app, false);
	int br = 0;
	ll ans = 0;

	for(int i = 0; i <= x; i += k) {
		ans += a[i];
		app[i] = true;
		br++;
	}

	for(int i = x; i >= 0 && br < n; i--) {
		if (app[i]) continue;
		br++;
		ans += a[i];
		app[i] = true;
	}
	printf("%lld\n", ans);
	return 0;
}