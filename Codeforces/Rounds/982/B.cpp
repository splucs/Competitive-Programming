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
#define MAXN 400309
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

char s[MAXN];
int w[MAXN], n;

int main() {
	priority_queue<ii> pq1, pq2;
	scanf("%d", &n);
	FOR1(i, n) {
		scanf("%d", &w[i]);
		pq1.push(ii(-w[i], i));
	}
	scanf(" %s", s);
	FOR(i, 2*n) {
		if (s[i] == '0') {
			int j = pq1.top().se;
			pq1.pop();
			printf("%d ", j);
			pq2.push(ii(w[j], j));
		}
		if (s[i] == '1') {
			int j = pq2.top().se;
			pq2.pop();
			printf("%d ", j);
		}
	}
	printf("\n");
	return 0;
}