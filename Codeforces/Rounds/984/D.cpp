#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 5009
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

int arr[MAXN][MAXN], mx[MAXN][MAXN];

int main() {
	int n;
	scanf("%d", &n);
	FOR1(i, n) {
		scanf("%d", &arr[1][i]);
		mx[1][i] = arr[1][i];
	}
	for(int i = 2; i <= n; i++) {
		FOR1(j, n-i+1) {
			arr[i][j] = arr[i-1][j]^arr[i-1][j+1];
			mx[i][j] = arr[i][j];
			if (mx[i][j] < mx[i-1][j]) mx[i][j] = mx[i-1][j];
			if (mx[i][j] < mx[i-1][j+1]) mx[i][j] = mx[i-1][j+1];
		}
	}
	int Q;
	scanf("%d", &Q);
	while (Q --> 0) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", mx[r-l+1][l]);
	}
	return 0;
}