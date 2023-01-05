#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 509
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884L
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=(n)-1; (x)>=0; (x)--)
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

int dp[2][MAXN][MAXN][2];
int n, m, K;
char classes[MAXN][MAXN];
int sum[MAXN][MAXN];

int main() {
	scanf("%d %d %d", &n, &m, &K);
	FOR(i, n) scanf(" %s", classes[i]);
	REP(i, n) {
		sum[i][m] = 0;
		REP(j, m) sum[i][j] = (classes[i][j] == '1' ? 1 : 0) + sum[i][j+1];
	}
	REP(i, n+1) REP(j, m+1) FOR(k, K+1) FOR(r, 2) {
		if (i == n) dp[i%2][j][k][r] = 0;
		else if (j == m) dp[i%2][j][k][r] = dp[(i+1)%2][0][k][0];
		else {
			//at home
			if (r == 0) {
				if (classes[i][j] == '1') {
					dp[i%2][j][k][r] = min(k >= 1 ? dp[i%2][j+1][k-1][0] : INF, 1 + dp[i%2][j+1][k][1]);
				}
				else {
					dp[i%2][j][k][r] = dp[i%2][j+1][k][r];
				}
			}
			//at school
			else {
				dp[i%2][j][k][r] = min(k >= sum[i][j] ? dp[(i+1)%2][0][k-sum[i][j]][0] : INF, 1 + dp[i%2][j+1][k][1]);
			}
		}
	}
	printf("%d\n", dp[0][0][K][0]);
	return 0;
}