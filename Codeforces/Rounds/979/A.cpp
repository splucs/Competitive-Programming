#include <bits/stdc++.h>
using namespace std;
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 100309
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define ROF(x,n) for(int x=(n)-1; (x)>=0; (x)--)
#define ROF1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int main() {
	ll n;
	scanf("%I64d", &n);
	if (n == 0) {
		printf("0\n");
		return 0;
	}
	n++;
	if (n % 2 == 0) n /= 2;
	printf("%I64d\n", n);
	return 0;
}