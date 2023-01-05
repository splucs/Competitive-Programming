#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 2009
#define MAXM 10
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

int dp[MAXN][10][10][10];
int a[MAXN], b[MAXN], n;

int main() {
	scanf("%d", &n);
	FOR1(i, n) scanf("%d %d", &a[i], &b[i]);
	for(int i = n; i >= 1; i--) {
		FOR(a1, 10) FOR(a2, 10) FOR(a3, 10) {

			vi path;
			path.pb(a[i]);
			path.pb(b[i]);
			if (a1 != 0) path.pb(a1);
			if (a2 != 0) path.pb(a2);
			if (a3 != 0) path.pb(a3);
			sort(path.begin()+1, path.end());
			dp[i][a1][a2][a3] = INF;
			do {
				int sum = 0;
				int left = path.size();
				int psz = path.size();
				FOR(it, psz) {
					left--;

					if (i < n) {
						if (left <= 3) {
							int cost = sum + dp[i+1][left > 0 ? path[psz-1] : 0][left > 1 ? path[psz-2] : 0][left > 2 ? path[psz-3] : 0] + abs(path[it]-a[i+1]);
							if (dp[i][a1][a2][a3] > cost) dp[i][a1][a2][a3] = cost;
						}
					}
					else {
						if (left == 0) {
							int cost = sum;
							if (dp[i][a1][a2][a3] > cost) dp[i][a1][a2][a3] = cost;
						}
					}

					if (left != 0) {
						sum += abs(path[it+1] - path[it]);
					}
				}
			} while(next_permutation(path.begin()+1, path.end()));
		}
	}
	printf("%d\n", dp[1][0][0][0] + 2*n + abs(1-a[1]));
	return 0;
}