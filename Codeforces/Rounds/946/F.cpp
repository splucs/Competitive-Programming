#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 109
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884L
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

int d[MAXN][MAXN][MAXN], c[MAXN][MAXN][MAXN];
char s[MAXN];
int n, x;
int b[MAXN];

void KMP() {
	b[0] = -1;
	for(int i = 0, j = -1; i < n;) {
		while (j >= 0 && s[i] != s[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
}

int main() {
	scanf("%d %d %s", &n, &x, s);
	KMP();

	//f0
	FOR(i, n) FOR(j, n) d[0][i][j] = c[0][i][j] = 0;
	FOR(i, n) {
		int j = i;
		while (j >= 0 && '0' != s[j]) j = b[j];
		j++;
		if (j == n) {
			j = b[j];
			assert(j >= 0);
			d[0][i][j%n]++;
		}
		c[0][i][j%n]++;
	}
	FOR(i, n) c[0][i][i]++;

	//f1
	FOR(i, n) FOR(j, n) d[1][i][j] = c[1][i][j] = 0;
	FOR(i, n) {
		int j = i;
		while (j >= 0 && '1' != s[j]) j = b[j];
		j++;
		if (j == n) {
			j = b[j];
			assert(j >= 0);
			d[1][i][j%n]++;
		}
		c[1][i][j%n]++;
	}
	FOR(i, n) c[1][i][i]++;

	//fn
	for(int f = 2; f <= x; f++) {
		FOR(i, n) FOR(j, n) {
			c[f][i][j] = 0;
			FOR(k, n) c[f][i][j] = (c[f][i][j] + c[f-1][i][k]*1ll*c[f-2][k][j])%MOD;
			d[f][i][j] = 0;
			FOR(k, n) {
				d[f][i][j] = (d[f][i][j] + d[f-1][i][k]*1ll*c[f-2][k][j])%MOD;
				d[f][i][j] = (d[f][i][j] + c[f-1][i][k]*1ll*d[f-2][k][j])%MOD;
			}
		}
	}

	int ans = 0;
	FOR(i, n) ans = (ans + d[x][0][i]) % MOD;

	printf("%d\n", ans);

	return 0;
}